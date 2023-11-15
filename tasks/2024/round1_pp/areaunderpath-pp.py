#!/usr/bin/env python3

lp = 10**9+7

def dp(n, m, p, r):
    memory = [[[0]*p for j in range(m+1)] for i in range(n+1)]
    for i in range(n+1):
        memory[i][0][0] = 1
    for j in range(m+1):
        memory[0][j][0] = 1
    for i in range(1, n+1):
        for j in range(1, m+1):
            for R in range(p):
                memory[i][j][R] = (memory[i][j-1][R] +
                                   memory[i-1][j][(R-j) % p]) % lp
    return memory[n][m][r]

n, m, p, r = map(int, input().split())
print(dp(n, m, p, r))
