#!/usr/bin/env python
import os
import shutil
import subprocess
import difflib
import filecmp
import sys

rootdir = "."

for subdir, dirs, files in os.walk(rootdir):
    for file in files:
        if "RLBin" in (os.path.join(subdir, file)):
        	os.remove(os.path.join(subdir, file))
        	print(os.path.join(subdir, file) + "    removed" )