#!/usr/bin/env python3
# @check-accepted: examples cubic quadratic
# @check-time-limit-exceeded: all

from sys import setrecursionlimit

setrecursionlimit(250_000)

N = int(input().strip())
G = [[] for _ in range(N)]
for _ in range(N-1):
    a, b = map(int, input().strip().split())
    G[a].append(b)
    G[b].append(a)

dp = [None] * N
ans = [None] * N


def cost(a):
    return sum(a) - max(a) + 1


def dfs1(v, p):
    dp[v] = [dfs1(u, v) for u in G[v] if u != p] + [0]
    dp[v].sort(reverse=True)
    return cost(dp[v])


def dfs2(v, p):
    s = sum(dp[v]) + 1
    ans[v] = s - dp[v][0]
    for u in G[v]:
        if u == p:
            continue
        c = cost(dp[u])
        s1 = s - c - dp[v][dp[v][0] == c]
        dp[u].append(s1)
        dp[u].sort(reverse=True)
        dfs2(u, v)
    return ans


dfs1(0, -1)
dfs2(0, -1)
for i in range(N):
    print(ans[i], end=' ')
print()
