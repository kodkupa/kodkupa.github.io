#!/usr/bin/env python3
# @check-accepted: examples NQbrute DSmall NoSweetness no-limits
# The python equivalent of the official .cpp solution  
# Very non pythonic

import sys

Vmax = 1_000_000

# we prep the auxiliary lists
freq = [0] * (2 * Vmax + 1)
sp = [0] * (2 * Vmax + 1)

# input data
N, P = map(int, input().strip().split())

S = list(map(int, input().strip().split()))

F = list(map(int, input().strip().split()))

Q = int(input().strip())

# actual computation of the frequency array
for i in range(N):
    if F[i] == P:
        freq[S[i] + Vmax] += 1

# partial sum of the freq array

sp[0] = freq[0]
for i in range(1, 2 * Vmax + 1):
    sp[i] = sp[i - 1] + freq[i]

# processing the preferences
for i in range(Q):
    [l, r, k] = map(int, input().strip().split())
    l += Vmax
    r += Vmax
    exterior = 0
    if l != 0:
        exterior = sp[l - 1]
    if sp[r] - exterior >= k:
        print('YES')
    else:
        print('NO')

sys.stdout.close()
