#!/usr/bin/env python3
# @check-accepted: *
# passes with pypy on cms

from sys import stdin
input = stdin.readline

def solv():
    N = int(input().strip())
    A = list(map(int, input().strip().split()))
    B = list(map(int, input().strip().split()))

    def test(val):
        prev=0
        for i in range(N-1):
            if A[i]+prev<val:
                if A[i]+prev+B[i]<val:
                    return False
                else:
                    prev=A[i]+prev+B[i]-val
            else:
                prev=B[i]
        if A[-1]+prev<val:
            return False
        return True

    lo=0
    hi=2*10**9+1
    #hi=max(A)+max(B)+1
    while hi-lo>1:
        mid=(hi+lo)//2
        if test(mid):
            lo=mid
        else:
            hi=mid
    print(lo)

for _ in range(int(input())):
    solv()
