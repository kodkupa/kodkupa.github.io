#!/usr/bin/env python3
# Full solution: every path costs N*M - 1, O(1) per query.

T = int(input())
for _ in range(T):
    N, M, K = map(int, input().split())
    print("YES" if K == N * M - 1 else "NO")
