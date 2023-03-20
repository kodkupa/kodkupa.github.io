#!/usr/bin/env python3
# @check-accepted: examples brute Nsmall no-limits
# insert brief description of the solution here


# input data
mod = 10**9 + 7
N, K = map(int, input().strip().split())
V = list(map(int, input().strip().split()))

cnt = [0] * N
cnt[0] = K
ans = 1

for x in V:
    ans = (ans * cnt[x]) % mod
    cnt[x] -= 1
    cnt[x + 1] += 1

print(ans)  # print the result
