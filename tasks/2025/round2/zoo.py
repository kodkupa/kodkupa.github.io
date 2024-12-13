#!/usr/bin/env python3
# passes with pypy

from collections import deque
from sys import stdin
input=stdin.readline

def main():
    N, M = map(int, input().split())

    # Build the graph
    g = [[] for _ in range(N)]
    for _ in range(M):
        a,b = map(int, input().split())
        g[a].append(b)
        g[b].append(a)

    # BFS function
    def bfs(src):
        q = deque([src])
        dist = [N] * N
        dist[src] = 0
        while q:
            n = q.popleft()
            for x in g[n]:
                if dist[n] + 1 < dist[x]:
                    dist[x] = dist[n] + 1
                    q.append(x)
        return dist

    # Calculate distances from start and end
    d_start = bfs(0)
    d_end = bfs(N - 1)
    d = d_start[-1]

    # Prefix sums for distances from the end
    pref_sum = [0] * (N + 3)
    for x in d_end:
        pref_sum[x + 2] += 1
    for i in range(1, N + 3):
        pref_sum[i] += pref_sum[i - 1]

    # Calculate the result
    ans = N * (N - 1) // 2 - M
    for x in d_start:
        ans -= pref_sum[max(0, d - x)]

    print(ans)

if __name__ == "__main__":
    main()
