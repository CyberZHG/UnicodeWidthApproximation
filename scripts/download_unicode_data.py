import time
import urllib.request
from pathlib import Path

UNICODE_VERSION = "17.0.0"
BASE_URL = f"https://www.unicode.org/Public/{UNICODE_VERSION}/ucd/"
OUTPUT_DIR = Path(__file__).parent.parent / "ucd"

FILES = [
    "EastAsianWidth.txt",
    "extracted/DerivedGeneralCategory.txt",
    "emoji/emoji-data.txt",
]


def download_file(filename: str):
    url = BASE_URL + filename
    output_path = OUTPUT_DIR / filename.split("/")[-1]

    print(f"Downloading {filename}...")
    try:
        request = urllib.request.Request(
            url,
            headers={"User-Agent": "Mozilla/5.0"}
        )
        with urllib.request.urlopen(request) as response:
            with open(output_path, "wb") as f:
                f.write(response.read())
        print(f"  Saved to {output_path}")
    except Exception as e:
        print(f"  Error: {e}")


def main():
    if not OUTPUT_DIR.exists():
        OUTPUT_DIR.mkdir(exist_ok=True)
    for filename in FILES:
        download_file(filename)
        time.sleep(1)


if __name__ == "__main__":
    main()
