#!/usr/bin/env python3
# @check-accepted: examples C=1 no-limits
# insert brief description of the solution here


# input data
N, R, C = list(map(int, input().strip().split()))


# insert your code here

if N > R * C:
    print('NEM')  # print the result
else:
    print('IGEN')  # print the result
