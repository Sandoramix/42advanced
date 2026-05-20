#!/usr/bin/env python3

from collections import deque
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path
from urllib.parse import urlparse, urljoin

from bs4 import BeautifulSoup
import requests
from requests.adapters import Retry, HTTPAdapter
from argparse import ArgumentParser, ArgumentTypeError

from tqdm import tqdm


# -----------------------
# CONFIG
# -----------------------

MAX_WORKERS = 10
TIMEOUT = 10

ALLOWED_EXTENSIONS = {
    ".jpg", ".png", ".jpeg", ".gif", ".bmp"
}


# -----------------------
# CLI
# -----------------------

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
    description="Download media from a URL."
)

parser.add_argument("url", type=str)

parser.add_argument(
    "-r",
    "--recursive",
    action="store_true",
    help="Recursively scan linked pages."
)

parser.add_argument(
    "-l",
    "--depth",
    type=depth_type,
    default=None
)

parser.add_argument(
    "-p",
    "--output-dir",
    type=Path,
    default=Path("./data"),
)

args = parser.parse_args()

if args.depth is not None and not args.recursive:
    parser.error("-l/--depth requires -r/--recursive")


# -----------------------
# HTTP SESSION
# -----------------------

session = requests.Session()

retries = Retry(
    total=3,
    connect=3,
    read=3,
    backoff_factor=1,
    allowed_methods=["GET", "HEAD"]
)

adapter = HTTPAdapter(
    max_retries=retries,
    pool_connections=20,
    pool_maxsize=20
)

session.mount("http://", adapter)
session.mount("https://", adapter)


# -----------------------
# HELPERS
# -----------------------

def is_media_file(url: str) -> bool:
    path = urlparse(url).path.lower()
    return any(path.endswith(ext) for ext in ALLOWED_EXTENSIONS)


def safe_filename(url: str) -> Path:
    parsed = urlparse(url)
    path = parsed.path.lstrip("/")

    if not path or path.endswith("/"):
        path = "index.html"

    return args.output_dir / path


# -----------------------
# CRAWLER
# -----------------------

def fetch_links(base_url: str):
    try:
        response = session.get(base_url, timeout=TIMEOUT)

        if "text/html" not in response.headers.get("Content-Type", ""):
            return []

        soup = BeautifulSoup(response.text, "html.parser")

        links = []

        for tag in soup.find_all("a", href=True):
            href = tag["href"]

            if href.startswith(("#", "mailto:", "javascript:")):
                continue

            full_url = urljoin(base_url, href)
            links.append(full_url)

        return links

    except requests.RequestException:
        return []


# -----------------------
# DOWNLOADER
# -----------------------

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

        return True, url, None

    except requests.RequestException as e:
        return False, url, str(e)


# -----------------------
# CRAWL STATE
# -----------------------

visited = set()
media_files = set()

queue = deque([(args.url, 0)])


# -----------------------
# BFS CRAWL
# -----------------------

while queue:
    current_url, depth = queue.popleft()

    if current_url in visited:
        continue

    visited.add(current_url)

    links = fetch_links(current_url)

    for link in links:

        if not link:
            continue

        if is_media_file(link):
            media_files.add(link)

        elif args.recursive and (
            args.depth is None or depth < args.depth
        ):
            queue.append((link, depth + 1))


print(f"Found {len(media_files)} files")


# -----------------------
# DOWNLOAD PHASE
# -----------------------

with ThreadPoolExecutor(max_workers=MAX_WORKERS) as executor:

    futures = [
        executor.submit(download_file, url)
        for url in media_files
    ]

    success = 0
    failed = []

    with tqdm(total=len(futures), desc="Downloading", unit="file") as pbar:

        for future in as_completed(futures):
            ok, url, err = future.result()

            if ok:
                success += 1
            else:
                failed.append((url, err))

            pbar.update(1)


print(f"\nDownloaded {success}/{len(media_files)} files")

if failed:
    print("\nFailures:")
    for url, err in failed:
        print(f"- {url} -> {err}")