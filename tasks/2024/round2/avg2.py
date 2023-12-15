#!/usr/bin/env python3
# @check-accepted: examples Ntwo VKsmall Nsmall no-limits
# insert brief description of the solution here


# input data
N,K = map(int,input().strip().split())
V = list(map(int, input().strip().split()))

K *= N
S = 0
for i in V:
    S += i

if S == K:
    print(0)
elif S < K:
    print((K - S + N - 1)//N)
else:
    upper = 10**9
    lower = 0
    while upper >= lower:
        mid = (upper + lower)//2
        s = S
        for i in V:
            s -= min(i-1, mid)
        if s > K:
            lower = mid + 1
        else: 
            upper = mid - 1
    print(lower)
