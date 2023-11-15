#!/usr/bin/env python3
# construction
# passes all tests?


# input data
N = int(input().strip())

# insert your code here

if N<2:
    print('-1')
else:
    if N%2==0:
        print('15'*(N//2))
    else:
        print('111'+'15'*((N-3)//2))
