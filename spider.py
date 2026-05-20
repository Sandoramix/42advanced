#!/usr/bin/env python3
import os
from collections import deque
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path
from urllib.parse import urlparse, urljoin

from bs4 import BeautifulSoup
import requests
import time
from requests.adapters import Retry, HTTPAdapter
from argparse import ArgumentParser, ArgumentTypeError

from tqdm import tqdm

MAX_WORKERS = 10
TIMEOUT = 10
ALLOWED_EXTENSIONS = ['.jpg', '.png', '.jpeg', '.gif', '.bmp']

def depth_type(value: str) -> int:
    try:
        depth = int(value)
    except ValueError:
        raise ArgumentTypeError("DEPTH must be an integer")

    if depth < 0:
        raise ArgumentTypeError("DEPTH must be >= 0")

    return depth


parser = ArgumentParser(
    prog="spider",
    usage="./%(prog)s [-r] [-l DEPTH] [-p DIR] URL",
    description="Download images from a URL."
)

parser.add_argument(
    "url",
    metavar="URL",
    type=str,
    help="Target URL to scan for images.",
)

parser.add_argument(
    "-r",
    "--recursive",
    action="store_true",
    help="Recursively scan linked pages for images."
)

parser.add_argument(
    "-l",
    "--depth",
    metavar="DEPTH",
    type=depth_type,
    default=None,
    help=(
        "Maximum recursion depth. "
        "Requires -r."
    )
)

parser.add_argument(
    "-p",
    "--output-dir",
    metavar="DIR",
    type=Path,
    default=Path("./data"),
    help="Directory where images will be saved."
)

args = parser.parse_args()

if args.depth is not None and not args.recursive:
    parser.error("-l/--depth requires -r/--recursive")

session = requests.Session()

retries = Retry(
    total=3,
    connect=3,
    read=3,
    backoff_factor=1,
    allowed_methods=["GET", "HEAD"]
)

adapter = HTTPAdapter(max_retries=retries, pool_connections=20, pool_maxsize=20)

session.mount("http://", adapter)
session.mount("https://", adapter)

# UTILS

def is_media_file(url: str) -> bool:
    path = urlparse(url).path.lower()
    return any(path.endswith(ext) for ext in ALLOWED_EXTENSIONS)


def safe_filename(url: str) -> Path:
    parsed = urlparse(url)
    path = parsed.path.lstrip("/")

    if not path:
        path = "index.html"

    return args.output_dir / path
def fetch_links(url: str):
    """
    Fetch all links from a page.
    """
    try:
        response = session.get(url, timeout=TIMEOUT)

        if "text/html" not in response.headers.get("Content-Type", ""):
            return []

        soup = BeautifulSoup(response.text, "html.parser")

        links = []

        for tag in soup.find_all("a", href=True):
            full_url = urljoin(url, tag["href"])
            links.append(full_url)

        return links

    except requests.RequestException:
        return []


def download_file(url: str):
    try:
        response = session.get(url, stream=True, timeout=TIMEOUT)
        response.raise_for_status()

        filepath = safe_filename(url)
        filepath.parent.mkdir(parents=True, exist_ok=True)

        with open(filepath, "wb") as f:
            for chunk in response.iter_content(chunk_size=8192):
                if chunk:
                    f.write(chunk)

        return True

    except requests.RequestException:
        return False

visited = set()
media_files = set()

queue = deque([(args.url, 0)])

while queue:
    current_url, depth = queue.popleft()

    if current_url in visited:
        continue

    visited.add(current_url)

    links = fetch_links(current_url)

    for link in links:

        if is_media_file(link):
            media_files.add(link)

        elif args.recursive and (args.depth is None or depth < args.depth):
            queue.append((link, depth + 1))


print(f"Found {len(media_files)} files")

with ThreadPoolExecutor(max_workers=MAX_WORKERS) as executor:

    futures = [
        executor.submit(download_file, url)
        for url in media_files
    ]

    success = 0

    with tqdm(total=len(futures), desc="Downloading", unit="file") as pbar:

        for future in as_completed(futures):
            if future.result():
                success += 1

            pbar.update(1)

print(f"Downloaded {success}/{len(media_files)} files")