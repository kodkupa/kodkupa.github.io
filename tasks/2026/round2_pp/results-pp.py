#!/usr/bin/env python3
# @check-accepted: examples two-distinct type1 type2 no-limits
# insert brief description of the solution here


# input data
N = int(input().strip())
R = list(map(int, input().strip().split()))

pos = 1
A = [1]
B = [1]

for i in range(1, N):
    if R[i - 1] != R[i]:
        pos += 1
        A.append(pos)
        B.append(i + 1)
    else:
        A.append(A[-1])
        B.append(B[-1])

assert A == R or B == R

if A == R:
    print(*B)
else: 
    print(*A)

