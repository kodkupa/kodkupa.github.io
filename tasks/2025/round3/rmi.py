#!/usr/bin/env python3
# @check-accepted: *

from sys import stdin
input = stdin.readline

# input data
A, B, N = list(map(int, input().split()))
F = list(map(int, input().split()))
S = list(map(int, input().split()))

S.sort()
F.sort()
summa = A + B

i = N - 1
j = 0
best = 1
while i >= 0:
    if F[i] + S[j] > summa:
        best += 1
        i -= 1
    else:
        i -= 1
        j += 1

worst = 1
i = N - 1
j = 0
while j < N:
    if F[i] + S[j] > summa:
        worst += 1
        i -= 1
        j += 1
    else:
        j += 1


print(best, worst)
