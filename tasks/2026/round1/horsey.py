#!/usr/bin/env python3

# @check-accepted: examples small-board medium-board no-limits


from math import gcd

t = int(input().strip())
for test in range(t):
    n, m, h, w = map(int, input().split(' '))
    possible = True
    if gcd(h, w) != 1:
        possible = False
    if h % 2 == w % 2:
        possible = False
    if max(m, n) < 2 * max(h, w):
        possible = False
    if min(m, n) < h + w:
        possible = False

    if possible:
        print("YES")
    else:
        print("NO")
