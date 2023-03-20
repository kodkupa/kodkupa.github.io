#!/usr/bin/env python3
# @check-accepted: examples N2 S2 Nsmall distinct no-limits

# input data
N = int(input().strip())
S = list(map(int, input().strip().split()))

S = S[::-1]
ans = 0
maxi = 0
for x in S:
    if x >= maxi:
        maxi = x
        ans += 1

print(ans)
