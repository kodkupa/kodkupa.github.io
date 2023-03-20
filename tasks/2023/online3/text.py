#!/usr/bin/env python3
# full score
# @check-accepted: *

n, k = map(int, input().strip().split())
t = [input().strip() for i in range(n)]

cnt = [[0]*26 for i in range(k)]
for s in t:
    for i in range(k):
        cnt[i][ord(s[i]) - ord('a')] += 1

ans = 0
mind = n * k
for i in range(n):
    d = 0
    for j in range(k):
        d += n - cnt[j][ord(t[i][j]) - ord('a')]
    if d < mind:
        mind = d
        ans = i

print(ans)