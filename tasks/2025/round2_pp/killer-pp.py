#!/usr/bin/env python3
# @check-accepted: examples brute quadratic linear no-limits

T = int(input().strip())
for _ in range(T):
    N, K = map(int, input().strip().split())
    t = K * (K + 1) // 2
    if K == 1 or N == t or N == t + 1:
        print("YES")
    else:
        print("NO")
