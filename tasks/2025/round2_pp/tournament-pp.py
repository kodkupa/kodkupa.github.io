#!/usr/bin/env python3
# @check-accepted: examples N2 Nsmall no-limits
import sys

N = int(input().strip())

P = list(map(int, input().strip().split()))

winner = 0
runnerup = 0

A = max(P[:N//2])
B = max(P[N//2:])
if A > B:
    winner = P.index(A)
    runnerup = P.index(B)
else:
    winner = P.index(B)
    runnerup = P.index(A)


print(winner, runnerup)

sys.stdout.close()
