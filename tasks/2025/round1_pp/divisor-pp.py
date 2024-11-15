#!/usr/bin/env python3
# @check-accepted: *

from itertools import product

def primeFactor(n):
    res=[]
    i=2
    while i*i<=n:
        cur=0
        while n%i==0:
            cur+=1
            n//=i
        if cur!=0:
            res.append((i,cur))
        i+=1
    if n>1:
        res+=[(n,1)]
    return res

def sol():
    a,b,k = map(int, input().strip().split())
    primes=primeFactor(a+b+k)
    res=1
    for A in product(*[range(n+1) for p,n in primes]):
        cur=1
        for i in range(len(primes)):
            cur*=primes[i][0]**A[i]
        if cur>res:
            i=a//cur
            if a <= cur*i <= a+k or a <= cur*(i+1) <= a+k:
                res=cur
    return res 

for t in range(int(input())):
    print(sol())
