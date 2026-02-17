#!/usr/bin/env python3
# @check-accepted: *


def solv():
    lo, hi, pos = map(int, input().split())
    buttons = input().strip()
    for b in buttons:
        if b == 'U':
            pos += 1
        elif b == 'D':
            pos -= 1
        else: # '0'
            pos = 0
        if pos < lo or hi < pos:
            return "error"
    return pos

print(solv())  # print the result
