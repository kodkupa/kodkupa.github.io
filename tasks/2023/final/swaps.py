#!/usr/bin/env python3
# @check-accepted: examples N<=8 N<=100 N<=5000 N<=1000000
# insert brief description of the solution here

from math import gcd

# input data
N = int(input().strip())
P = list(map(int, input().strip().split()))

g = 0
for i in range(len(P)):
    g = gcd(g, P[i]-(i+1))

ans1 = N
had = [0] * N
for i in range(N):
    if not had[i]:
        ans1 -= 1
        while not had[i]:
            had[i] = 1
            i = P[i] - 1

ans2 = list()
if g==0:
    for i in range(1,N+1):
        ans2.append(i)
else:
    for i in range(1,g+1):
        if g%i==0:
            ans2.append(i)

res = [-1] * (N+1)
for i in ans2:
    res[i] = ans1
print(*res[1:])
