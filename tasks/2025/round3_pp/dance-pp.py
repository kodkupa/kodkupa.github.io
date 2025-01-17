#!/usr/bin/env python3
# @check-accepted: examples NDsmall Nsmall Dsmall no-limits

N = int(input())
D = int(input())
A = list(map(int, input().split()))
B = list(map(int, input().split()))

ok = True
for i in range(N):
    if B[i]-D <= A[i] < B[i]:
        continue
    else:
        ok = False
        break

if ok:
    print('YES')
else:
    print('NO')
