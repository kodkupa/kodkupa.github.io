#!/usr/bin/env python3
# @check-accepted: examples N1 NMsmall no-limits
# insert brief description of the solution here


# input data
N,M = list(map(int, input().strip().split()))
A = list(map(int, input().strip().split()))
B = list(map(int, input().strip().split()))

peaksA = 0
peaksB = 0

for i in range(N):
    if (i == 0 or A[i] > A[i-1]) and (i == N-1 or A[i] > A[i+1]):
        peaksA += 1

for i in range(M):
    if (i == 0 or B[i] > B[i-1]) and (i == M-1 or B[i] > B[i+1]):
        peaksB += 1

print(peaksA * peaksB)  
