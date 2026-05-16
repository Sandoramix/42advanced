#!/usr/bin/env python3
import os
from pathlib import Path

from bs4 import BeautifulSoup
import requests
import time
from requests.adapters import Retry, HTTPAdapter
from argparse import ArgumentParser, ArgumentTypeError


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
    required=True
)

parser.add_argument(
    "-r",
    action="store_false",
    help="Recursively scan linked pages for images."
)

parser.add_argument(
    "-l",
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


def listFD(url):
    try:
        retry = Retry(total=10, connect=5, read=5, allowed_methods=['GET'], backoff_factor=10)
        session = requests.Session()
        session.mount('http://', HTTPAdapter(max_retries=retry))
        session.mount('https://', HTTPAdapter(max_retries=retry))
        page_content = session.get(url).text
        soup = BeautifulSoup(page_content, 'html.parser')
        return [url + '/' + node.get('href') for node in soup.find_all('a') if node.get('href')]
    except:
        return []


if not os.path.exists(args.output_dir) or not os.path.isdir(args.output_dir) or not os.access(args.output_dir, os.W_OK):
    print(f"Directory {args.output_dir} does not exist or is not writable")
    exit(1)

files = listFD(args.url)

allowed_extensions = ['.jpg', '.png', '.jpeg', '.gif', '.bmp']


index = 0
for file in files:
    if (file.endswith(tuple(allowed_extensions)) or file.endswith('../')):
        continue
    if index == 100:
        time.sleep(1)
        index = 0
    if file.endswith('/') and not file.endswith('/../'):
        files.extend(listFD(file[:len(file) - 1]))
    elif file.endswith('/../'):
        continue
    else:
        try:
            page = requests.get(file).text
            with open(args.output_dir / file.replace(args.url, ''), 'wb') as f:
                f.write(page)
            index += 1
        except:
            continue
f.close()
