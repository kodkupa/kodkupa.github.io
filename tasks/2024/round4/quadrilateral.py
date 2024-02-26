#!/usr/bin/env python3
# @check-accepted: examples Nsmall Nmid no-limits
# O(Nlog(N))

def solv():
    # input data
    N = int(input().strip())
    S = list(map(int, input().strip().split()))
    S.sort()
    for i in range(N-3):
        if S[i]+S[i+1]+S[i+2]>S[i+3]:
            print(S[i],S[i+1],S[i+2],S[i+3])
            return
    print('-1')

solv()
