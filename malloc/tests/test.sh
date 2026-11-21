#!/bin/sh

LIB="$PWD/libmalloc.so"
a_failed=0


tests()
{
    command -v "$1" >/dev/null 2>&1 || { echo "skip $*"; return; }
    if LD_PRELOAD="$LIB" "$@" > /dev/null 2>&1; then
        echo "ok   $*"
    else
        echo "pas ok $*"
        a_failed=1
    fi
}
tests ./tests/test
tests ls
tests ls -la
tests factor 20 30 40 50 60 70 80 90
tests find src tests
tests tree src
tests od libmalloc.so
tests git status
tests less Makefile 
tests ip a
tests tar -cf /tmp/malloc.tar libmalloc.so
rm -f /tmp/malloc.tar

exit $a_failed
