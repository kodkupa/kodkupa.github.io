#!/usr/bin/env python3
# @check-accepted: examples N=0 no-limits



# input data
M,N,K = list(map(int, input().strip().split()))


# insert your code here

if (N+M)%K == 0:
    print('IGEN')  # print the result
else:
    print('NEM')  # print the result
