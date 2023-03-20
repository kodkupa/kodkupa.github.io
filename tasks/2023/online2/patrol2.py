#!/usr/bin/env python3
# @check-accepted: *

n, m, l = map(int, input().strip().split())
g = [[] for _ in range(n)]
for _ in range(m):
    a, b = map(int, input().strip().split())
    g[a].append(b)
    g[b].append(a)
c = list(map(int, input().strip().split()))

dist = [1e8] * n
q = []
qf = 0
dist[0] = 0
q.append((0, 0))

while qf < len(q):
    d, v = q[qf]
    qf += 1
    if dist[v] != d: continue

    for u in g[v]:
        t = dist[v] + 1
        if dist[u] <= t: continue
        if c[t % len(c)] != u:
            dist[u] = t
            q.append((dist[u], u))
        elif t + 1 < dist[u]:
            dist[u] = t + 1
            q.append((dist[u], u))

print(dist[n - 1] if dist[n - 1] != 1e8 else -1)
