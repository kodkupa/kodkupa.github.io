#!/usr/bin/env pypy3

N, C = map(int, input().strip().split())
L = list(map(int, input().strip().split()))

mi = 1e9
r = 0
l = 0
luci = 0
count = [0 for i in range(N)]
for i in range(N):
    while r < N and luci < C:
        if count[L[r]] == 0:
            luci += 1
        count[L[r]] += 1
        r += 1
    if luci == C:
        mi = min(mi, r - l)
    while l < r and luci == C:
        count[L[l]] -= 1
        if count[L[l]] == 0:
            luci -= 1
        l += 1
        if luci == C:
            mi = min(mi, r - l)

print(mi)
