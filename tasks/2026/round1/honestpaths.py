#!/usr/bin/env python3
# @check-accepted: examples Nsmall GraphSmall
# @check-time-limit-exceeded: Tree UnitWeights no-limits

import sys
import heapq

data = list(map(int, sys.stdin.buffer.read().split()))
it = iter(data)
n = next(it)
m = next(it)
trg = n
vec = [[] for _ in range(n + 1)]
INF = 10**18
dist = [INF] * (n + 1)
dist[trg] = 0
dp = [0] * (n + 1)
nxt = [0] * (n + 1)
for _ in range(m):
    x = next(it)
    y = next(it)
    w = next(it)
    vec[x].append((w, y))
    vec[y].append((w, x))
pq = [(0, trg)]
while pq:
    cur, nod = heapq.heappop(pq)
    if dist[nod] != cur:
        continue
    for w, y in vec[nod]:
        if w + cur < dist[y]:
            dist[y] = w + cur
            heapq.heappush(pq, (dist[y], y))
ord_nodes = list(range(1, n + 1))
ord_nodes.sort(key=lambda a: dist[a])
rez = trg
for x in ord_nodes:
    for w, y in vec[x]:
        if dist[y] >= dist[x]:
            continue
        val = dp[y] + w
        if val > dp[x]:
            dp[x] = val
            nxt[x] = y
    if dp[x] > dp[rez]:
        rez = x
ans = []
x = rez
while x != 0:
    ans.append(x)
    x = nxt[x]
out = []
out.append(f"{dp[rez]} {len(ans)}")
out.append(" ".join(map(str, ans)))
sys.stdout.write("\n".join(out) + "\n")
