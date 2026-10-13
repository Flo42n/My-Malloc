#!/bin/sh
set -e

LD_PRELOAD=./libmalloc.so ls > /dev/null
LD_PRELOAD=./libmalloc.so ls -la > /dev/null
LD_PRELOAD=./libmalloc.so factor 20 30 40 50 60 70 80 90 > /dev/null
LD_PRELOAD=./libmalloc.so tar -cf malloc.tar libmalloc.so > /dev/null
LD_PRELOAD=./libmalloc.so find ../ > /dev/null
LD_PRELOAD=./libmalloc.so tree ../ > /dev/null
LD_PRELOAD=./libmalloc.so od libmalloc.so > /dev/null
LD_PRELOAD=./libmalloc.so git status > /dev/null
LD_PRELOAD=./libmalloc.so tar -cf malloc.tar "$LIB"
rm -f malloc.tar

