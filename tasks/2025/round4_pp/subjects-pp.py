#!/usr/bin/env python3
# @check-accepted: *

from sys import stdin
input = stdin.readline

def solv():
    N, M = map(int,input().split())
    notOK = set()
    for _ in range(N):
        K, *S = list(map(int, input().split()))
        S.sort()
        for i in range(K-1):
            for j in range(i+1, K):
                notOK.add((S[i],S[j]))
    print(M*(M-1)//2-len(notOK))
    for i in range(1,M):
        for j in range(i+1,M+1):
            if (i,j) not in notOK:
                print(i,j)

solv()
