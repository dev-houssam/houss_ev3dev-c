#!/usr/bin/env python3
"""Run the yupp preprocessor directly from the repository submodule."""

from pathlib import Path
import sys


def main():
    if sys.version_info < (3, 11):
        print(
            "yupp requires Python 3.11 or newer; set PYTHON to a supported "
            "interpreter",
            file=sys.stderr,
        )
        return 1

    yupp_src = Path(__file__).resolve().parents[1] / "yupp" / "src"
    if not yupp_src.is_dir():
        print(
            "yupp submodule is not initialized; run "
            "'git submodule update --init yupp'",
            file=sys.stderr,
        )
        return 1

    sys.path.insert(0, str(yupp_src))
    from yupp.__main__ import main as yupp_main

    return yupp_main()


if __name__ == "__main__":
    raise SystemExit(main())
