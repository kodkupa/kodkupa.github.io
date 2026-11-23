#!/usr/bin/env python3
# Python port of solution.cpp: O(N α(N)) BFS with a "next unscanned tile" pointer.
import sys


def main():
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    B = [int(x) for x in data[1:n + 1]]
    S = [int(x) for x in data[n + 1:2 * n + 1]]

    land = list(range(n))
    for k in range(n - 1, -1, -1):
        if S[k] != -1:
            land[k] = land[S[k]]

    nxt = list(range(n + 1))

    def find(x):
        root = x
        while nxt[root] != root:
            root = nxt[root]
        while nxt[x] != root:  # path compression
            nxt[x], x = root, nxt[x]
        return root

    dist = [-1] * n
    dist[0] = 0
    queue = [0]
    for u in queue:  # the list grows while we iterate: this is the BFS queue
        hi = u + B[u]
        d = dist[u] + 1
        j = find(u + 1)
        while j <= hi:
            nxt[j] = j + 1  # delete j
            v = land[j]
            if dist[v] == -1:
                dist[v] = d
                queue.append(v)
            j = find(j + 1)

    print(dist[n - 1])


main()
