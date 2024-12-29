#!/usr/bin/python3
# -*- coding: utf-8 -*-
import re
import sys
from pwb.__main__ import pwb
if __name__ == '__main__':
    sys.argv[0] = re.sub(r'(-script\.pyw|\.exe)?$', '', sys.argv[0])
    sys.exit(pwb())