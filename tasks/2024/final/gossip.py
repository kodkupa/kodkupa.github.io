#!/usr/bin/env python3
# @check-accepted: examples NQsmall Nsmall no-limits
# NOTE: it is recommended to use this even if you don't understand the following code.

import sys

# uncomment the two following lines if you want to read/write from files
# sys.stdin = open('input.txt')
# sys.stdout = open('output.txt', 'w')

N = int(input().strip())

P = list(map(int, input().strip().split()))

Q = int(input().strip())

A = [0 for i in range(Q)]
B = [0 for i in range(Q)]
for i in range(Q):
    A[i], B[i] = map(int, input().strip().split())

R = [0 for i in range(Q)]

cycle = [-1 for i in range(N)]
cycle_len = [0 for i in range(N)]
cycle_pos = [0 for i in range(N)]

for i in range(N):
    c = i
    while cycle[c] == -1:
        cycle[c] = i
        cycle_len[i] += 1
        cycle_pos[c] = cycle_len[i]
        c = P[c]

for i in range(Q):
    if cycle[A[i]] != cycle[B[i]]:
        R[i] = -1
    else:
        d = abs(cycle_pos[A[i]] - cycle_pos[B[i]])
        R[i] = min(d, cycle_len[cycle[A[i]]] - d)


for i in range(Q):
    print(R[i], end=' ')
print()

sys.stdout.close()
