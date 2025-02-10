#!/usr/bin/env python3
# @check-accepted: *

N, M = map(int, input().split())
C = list(map(int, input().split()))
P = list(map(int, input().split()))

maxChocolates = 0

for i in range(N):
    if C[i] % 2 == 0:
        if P[i] <= M:
            maxChocolates = max(maxChocolates, C[i])

print(maxChocolates)
