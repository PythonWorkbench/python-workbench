#!/usr/bin/env python3

import os, sys
import argparse
from . import pwb


def main():
    parser = argparse.ArgumentParser(description="A simple pwb CLI.")
    parser.add_argument("operation", choices=["info", "repo", "version"], 
                        help="The operation to perform")

    args = parser.parse_args()

    if args.operation == "info":
        print("Python Workbench")
    elif args.operation == "repo":
        print("repo":   ")
    elif args.operation == "version":
        print("0.1.0")
    else :
        print("Invalid operation")

if __name__ == "__main__":
    main()