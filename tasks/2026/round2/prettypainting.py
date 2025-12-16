#!/usr/bin/env python3
import sys

N = int(input().strip())

K = list(map(int, input().strip().split()))
P = [0] + list(map(int, input().strip().split()))
W = [0] + list(map(int, input().strip().split()))

dp = [0 for _ in range(N)]
dp2 = [0 for _ in range(N)]
adj = [[] for _ in range(N)]

for i in range(1, N):
    adj[P[i]].append(i)

for i in reversed(range(N)):
    cur_ans = sum(dp[x] for x in adj[i])
    gains = list(reversed(sorted([max(0, dp2[x] + W[x] - dp[x]) if K[x] > 0 else 0 for x in adj[i]])))
    dp2[i] = cur_ans + sum(gains[:max(0, K[i] - 1)])
    dp[i] = dp2[i] + (gains[K[i]-1] if 0 < K[i] <= len(gains) else 0)

print(dp[0])
sys.stdout.close()
