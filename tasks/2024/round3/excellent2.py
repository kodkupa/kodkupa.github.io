#!/usr/bin/env python3
# @check-accepted: Examples n<=20 n<=2000 n<=200000 n<=10^18
# python 3.8+

t = int(input().strip())
for _ in range(t):
    n=int(input().strip())
    print(((pow(2,n,10**9+7)+2*(-1)**n)*pow(3,-1,10**9+7))%(10**9+7))
