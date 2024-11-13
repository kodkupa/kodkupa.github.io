#!/usr/bin/env python3
# @check-accepted: examples NTtiny fit-int no-limits
# O(N*log(maxT))

from sys import stdin

input = stdin.readline

N = int(input().strip())
T = list(map(int, input().strip().split()))

books = 0
for topic in T:
    twopower = 2
    while topic > twopower - 1:
        twopower *= 2
    books += twopower - 1 - topic

print(books)
