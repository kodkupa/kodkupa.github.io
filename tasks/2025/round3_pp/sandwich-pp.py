#!/usr/bin/env python3
# @check-accepted: *

from bisect import bisect_left
from sys import stdin
input = stdin.readline

def LIS(a):
    lis = []
    for x in a:
        if x <= 0:
            continue
        pos = bisect_left(lis, x)
        if pos == len(lis):
            lis.append(x)
        else:
            lis[pos] = x
    return bisect_left(lis, a[-1]) + 1

def solv():
    N = int(input())
    A = list(map(int,input().split()))
    
    for i in range(1, N):
        A[i] += A[i - 1]
    
    print(LIS(A))

solv()
