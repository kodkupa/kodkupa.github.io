#!/usr/bin/env python3

T = int(input().strip())
for _ in range(T):
    N, L, K = map(int, input().strip().split())
    X = [-K] + list(map(int, input().strip().split())) + [L]

    ans = "NO"

    for i in range(1, N + 2):
        if X[i] - X[i - 1] >= 2 * K:
            ans = "YES"
            break

    print(ans)
