#!/usr/bin/env python3
# @check-accepted: examples Nsmall no-limits


N = int(input().strip())
K = int(input().strip())
S = int(input().strip())

if N * K < S:
    print('NO')
else:
    print('YES') 
