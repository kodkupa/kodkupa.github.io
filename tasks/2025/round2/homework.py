#!/usr/bin/env python3
# TLE with pypy...
from sys import stdin
input = stdin.readline

def solve():
    def lsb(a):
        return a & -a

    def add(a, b, mul):
        while a <= n:
            fen[a] += b * mul
            db[a] += mul
            a += lsb(a)

    def add1(a, b):
        while a <= n:
            fen[a] += b 
            db[a] += 1
            a += lsb(a)
            
    def ask(val):
        ans = 0
        pos = 0
        for i in range(19, -1, -1):
            next_pos = pos + 2**i
            if next_pos <= n and fen[next_pos] <= val:
                val -= fen[next_pos]
                pos = next_pos
                ans += db[next_pos]
        return ans

    def range_add(a, l, r, val):
        if left[a] > r or right[a] < l:
            return
        if l <= left[a] <= right[a] <= r:
            summ[a] += val
            mini[a] += val
            return
        x = 2 * a
        y = x + 1
        range_add(x, l, r, val)
        range_add(y, l, r, val)
        mini[a] = summ[a] + min(mini[x], mini[y])

    input()
    n, m = map(int, input().split())
    t=[0] * (n+1)
    h=[0] * (n+1)
    for i in range(1, n + 1):
        t[i], h[i] = map(int, input().split())
        
    tmp=[i for i in range(n+1)]
    order1 = sorted(tmp, key=lambda x: t[x])
    order2 = sorted(tmp, key=lambda x: h[x])

    inv2=[0]*(n+1)
    for i in range(1, n + 1):
        inv2[order2[i]] = i

    fen = [0] * (n+1)
    db = [0] * (n+1)
    for i in range(1, n + 1):
        add1(i, t[order1[i]])

    po = 1
    while po < n:
        po *= 2
    left = [0] * (2*po)
    right = [0] * (2*po)
    mini = [0] * (2*po)
    summ = [0] * (2*po)
    for i in range(po, 2 * po):
        left[i] = right[i] = i - po + 1
        if left[i] <= n:
            summ[i] = h[order2[left[i]]]
            mini[i] = summ[i]

    for i in range(po - 1, 0, -1):
        left[i] = left[2 * i]
        right[i] = right[2 * i + 1]
        mini[i] = min(mini[2 * i], mini[2 * i + 1])

    ans = ask(m)
    specsum = specdb = 0

    for i in range(1, n + 1):
        id = order1[i]
        add(i, t[id], -1)
        pos = inv2[id]
        range_add(1, pos, n, -t[id])
        specsum += t[id]
        specdb += 1
        if mini[1] >= 0:
            ans = max(ans, 2 * specdb + ask(m - specsum))
        else:
            range_add(1, pos, n, t[id])
            specsum -= t[id]
            specdb -= 1
            add1(i, t[id])
    print(ans,flush=False)

tc = int(input())
for _ in range(tc):
    solve()
