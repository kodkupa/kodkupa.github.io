#!/usr/bin/env pypy3
# @check-accepted: examples NVsmall Ntiny
# @check-time-limit-exceeded: no-cherry no-limits


import sys
input = sys.stdin.readline

def solve():
    N = int(input())
    A = [0]*N
    B = [0]*N
    C = [0]*N

    for i in range(N):
        A[i], B[i], C[i] = map(int, input().split())

    remaining = list(range(N))
    chosen = set()

    # sort by apples and bananas
    sa = sorted(remaining, key=lambda i: A[i])
    sb = sorted(remaining, key=lambda i: B[i])

    # pick max of sa and sb (forced baskets)
    forcedA = sa.pop()  # max apple
    forcedB = sb.pop()  # max banana
    chosen.add(forcedA)
    chosen.add(forcedB)
    if forcedA in sb:
        sb.remove(forcedA)
    if forcedB in sa:
        sa.remove(forcedB)

    # handle odd (pick leftover)
    if (len(sa) % 2) == 1:
        leftover = sa.pop()
        chosen.add(leftover)
        sb.remove(leftover)

    # build the 2-regular graph
    adj = [[] for _ in range(N)]
    for i in range(0, len(sa), 2):
        u, v = sa[i], sa[i+1]
        adj[u].append(v)
        adj[v].append(u)
    for i in range(0, len(sb), 2):
        u, v = sb[i], sb[i+1]
        adj[u].append(v)
        adj[v].append(u)

    # process cycles
    visited = set(chosen)
    chosen = list(chosen)
    for start in sa:
        if start in visited:
            continue
        cycle = []
        cur = start
        prev = -1
        while True:
            visited.add(cur)
            cycle.append(cur)
            nxt = adj[cur][0] if adj[cur][0] != prev else adj[cur][1]
            prev, cur = cur, nxt
            if cur == start:
                break

        # pick alternating nodes to maximize cherries
        sum_even = sum(C[cycle[i]] for i in range(0, len(cycle), 2))
        sum_odd = sum(C[cycle[i]] for i in range(1, len(cycle), 2))
        if sum_even >= sum_odd:
            for i in range(0, len(cycle), 2):
                chosen.append(cycle[i])
        else:
            for i in range(1, len(cycle), 2):
                chosen.append(cycle[i])

    # Step 5: output
    print(len(chosen))
    print(*chosen)


for t in range(int(input())):
    solve()
