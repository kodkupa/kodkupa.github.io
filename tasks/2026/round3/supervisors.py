#!/usr/bin/env python3
# @check-accepted: examples brute cubic line no-limits
import sys

def main() -> None:
    input = sys.stdin.readline

    N, K = map(int, input().split())
    S = list(map(int, input().split()))

    adj = [[] for _ in range(N)]
    P = list(map(int, input().split()))
    for i in range(1, N):
        adj[P[i - 1]].append(i)

    NEG_INF = -10**16

    dp = [[] for _ in range(N)]
    sz = [1] * N

    for i in range(N - 1, -1, -1):
        cur = [NEG_INF] * (N + 1)
        cur[0] = 0

        for x in adj[i]:
            max_t = sz[i] + sz[x] - 1
            for t in range(max_t, 0, -1):
                upper_j = min(t, sz[x])
                lower_j = max(1, t - sz[i])
                for j in range(lower_j, upper_j + 1):
                    if cur[t - j] == NEG_INF or dp[x][j] == NEG_INF:
                        continue
                    val = cur[t - j] + dp[x][j] + S[i] * j * (t - j)
                    if val > cur[t]:
                        cur[t] = val

            sz[i] += sz[x]

        for j in range(sz[i], 0, -1):
            if cur[j - 1] != NEG_INF:
                val = cur[j - 1] + S[i] * (j - 1)
                if val > cur[j]:
                    cur[j] = val

        dp[i] = cur

    print(dp[0][K])

if __name__ == "__main__":
    main()

