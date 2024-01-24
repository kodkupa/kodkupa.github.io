#!/usr/bin/env python3
# @check-accepted: examples K1 NKsmall NKmedium no-limits
# O(N)

from sys import stdin
input = stdin.readline


def k1(N, T):
    ans = 0
    for i in range(N):
        if i > 0 and T[i] == T[i-1] == 2:
            ans = 0
            break
        if T[i] == 1:
            ans += 1
    print(ans)


def solv():
    N, K = map(int, input().strip().split())
    tricks = list(map(int, input().strip().split()))
    M = int(input().strip())
    ok = set()
    for i in range(M):
        a, b = map(int, input().strip().split())
        ok.add((a, b))
    if N == 1:
        if tricks[0] <= K:
            print('1')
        else:
            print('0')
        return

    if K == 1:
        k1(N, tricks)
        return

    res = [0]*N
    if tricks[-1] <= K:
        res[-1] = 1
    if (tricks[-2], tricks[-1]) in ok:
        res[-2] = 2
    elif tricks[-2] <= K:
        res[-2] = 1
    for i in range(2, N+1):
        jump = 0
        if (tricks[-i], tricks[-i+1]) in ok:
            jump += 1
        if (tricks[-i], tricks[-i+2]) in ok:
            jump += 2
        if jump == 0:
            continue
        elif jump == 1:
            res[-i] = 1+res[-i+1]
        elif jump == 2:
            res[-i] = 1+res[-i+2]
        else:
            res[-i] = 1+max(res[-i+1], res[-i+2])
    print(max(res[0], res[1]))


solv()
