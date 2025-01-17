#!/usr/bin/env python3
# @check-accepted: *

def main():
    a = input().strip()
    b = input().strip()

    if a + 'a' == b:
        print(-1)
        return

    a += '0'
    b += '0'

    i = 0
    while True:
        if a[i] != b[i]: break
        i += 1

    if i + 1 < len(b) - 1:
        print(b[:i + 1])
        return

    if ord(b[i]) - ord(a[i]) > 1:
        print(b[:i] + chr(ord(b[i]) - 1))
        return

    i += 1
    while a[i] == 'z':
        i += 1

    print(a[:i] + 'z')

main()
