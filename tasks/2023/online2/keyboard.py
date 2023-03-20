#!/usr/bin/env pypy3
# @check-accepted: examples 2-digit NT<=1000 all
# insert brief description of the solution here

def dist(a, b, swapa, swapb, x):
    if x:
        if swapa == a:
            a = swapb
        elif a == swapb:
            a = swapa
    if swapa == b:
        b = swapb
    elif b == swapb:
        b = swapa
    return abs(b-a)


T = int(input().strip())
for _ in range(T):
    # input data
    S = input().strip()
    N = len(S)
    memo = [[[0]*10 for _ in range(10)] for _ in range(2)]
    cur = 0
    for i in range(N):
        if i:
            memo[cur][0][0] = memo[not cur][0][0] + dist(int(S[i - 1]), int(S[i]), 0, 0, 0)
        else:
            memo[cur][0][0] = dist(0, int(S[i]), 0, 0, 0)
        for j in range(10):
            for k in range(j + 1, 10):
                if i:
                    memo[cur][j][k] = min(memo[not cur][j][k] + dist(int(S[i - 1]), int(S[i]), j, k, 1),
                                          memo[not cur][0][0] + dist(int(S[i - 1]), int(S[i]), j, k, 0))
                else:
                    memo[cur][j][k] = dist(0, int(S[i]), j, k, 0)
        cur = not cur
    ans = 10**9
    for j in range(10):
        for k in range(j + 1, 10):
            ans = min(ans, memo[not cur][j][k])
    print(ans)
