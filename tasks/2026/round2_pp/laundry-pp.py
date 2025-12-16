#!/usr/bin/env python3
# @check-accepted: *

N, C, W = map(int, input().split())
T = list(map(int, input().split()))

T.sort(reverse = True)

ans = W

for i in range(0, N, C):
    if i+C<N:
        ans += max(W, T[i])
    else:
        ans += T[i]

print(ans)
