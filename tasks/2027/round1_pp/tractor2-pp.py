#!/usr/bin/env python3
# Full solution: Dijkstra on arrival times; on a road of the tractor path, binary search
# for the last tractor that left before us, O((M + N) log N + M log K).
import sys
from bisect import bisect_left
from heapq import heappush, heappop


def main():
    data = sys.stdin.buffer.read().split()
    N, M, K, L, U, V = map(int, data[:6])
    pos = 6
    X = data[pos : pos + M]; pos += M
    Y = data[pos : pos + M]; pos += M
    Z = data[pos : pos + M]; pos += M
    T = sorted(map(int, data[pos : pos + K])); pos += K
    P = list(map(int, data[pos : pos + L]))

    adj = [[] for _ in range(N)]
    for i in range(M):
        x, y, z = int(X[i]), int(Y[i]), int(Z[i])
        adj[x].append((y, z))
        adj[y].append((x, z))

    # directed road (P[i], P[i+1]) -> i, and the time offsets of the tractors along the path
    index = {}
    weight = {}
    for x in range(N):
        for y, z in adj[x]:
            weight[x * N + y] = z
    offsets = [0] * L
    for i in range(1, L):
        key = P[i - 1] * N + P[i]
        offsets[i] = offsets[i - 1] + V * weight[key]
        index[key] = i - 1

    INF = float("inf")
    dst = [INF] * N
    dst[0] = 0
    pq = [(0, 0)]
    while pq:
        d, x = heappop(pq)
        if d != dst[x]:
            continue
        base = x * N
        for y, z in adj[x]:
            arrival = d + z * U
            tpos = index.get(base + y)
            if tpos is not None:
                j = bisect_left(T, d - offsets[tpos])
                if j:
                    arrival = max(arrival, T[j - 1] + offsets[tpos + 1])
            if arrival < dst[y]:
                dst[y] = arrival
                heappush(pq, (arrival, y))

    print(dst[N - 1])


main()
