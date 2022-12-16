#!/usr/bin/env pypy3

# input data
N,Q = map(int, input().strip().split())
C = list(map(int, input().strip().split()))
cur = [0]*N
ans = 0

for j in range(Q):
    i,q = map(int, input().strip().split())
    if cur[i] + q <= C[i]:
        cur[i] += q
    else:
        ans += C[i] - cur[i]
        cur[i] = q

for i in range(N):
    if cur[i] > 0:
        ans += C[i] - cur[i]

print(ans)  # print the result
