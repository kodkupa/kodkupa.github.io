#!/usr/bin/env python3

import sys
input=sys.stdin.readline

dp={1:1, 2:1, 3:1, 4:1}

fib=[1,2]
while fib[-1]+fib[-2]<10**9:
    fib.append(fib[-1]+fib[-2])
# len(fib)=43

def solv(M):
    if M in dp:
        return dp[M]
    res=0
    for i in range(1,43):
        if M%fib[i]==0:
            res+=solv(M//fib[i])
    dp[M]=res
    return res

T = int(input().strip())
for test in range(1, T+1):
    M = int(input().strip())
    print(solv(M))
