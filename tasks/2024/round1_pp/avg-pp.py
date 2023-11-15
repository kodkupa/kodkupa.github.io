#!/usr/bin/env python3
# @check-accepted: examples NSmall NMedium no-limits
n, k = map(int, input().split())

p = list(map(int, input().split()))

s = sum(p)
if s==n*k:
    print(0)
elif s<n*k:
    print(1)
else:
    p = sorted(p)[::-1]
    ans, rem = 0, s-n*k
    for i in range(n):
        can = min(rem, p[i]-1)
        if can>0:
            ans+=1
            rem-=can
    
    print(ans)
