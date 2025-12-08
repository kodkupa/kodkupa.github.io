#!/usr/bin/env python3
# @check-accepted: examples equal max2 no-limits
# insert brief description of the solution here


# input data
A = int(input())
B = int(input())
C = int(input())


if A == B == C:
    print(1)
elif A == B or A == C or B == C:
    print(3)
else:
    print(6)

