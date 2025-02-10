#!/usr/bin/env python3
# @check-accepted: *

from math import ceil, sqrt

N, M, A = map(int, input().split())

res = 0

for w in range(1, ceil(sqrt(A)) + 1):
    if A % w == 0:
        h = A // w
        if w >= N and h >= M:
            res += 1
        if h >= N and w >= M and w != h:
            res += 1

print(res)
