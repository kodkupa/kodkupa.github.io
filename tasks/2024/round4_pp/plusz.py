#!/usr/bin/env python3
# @check-accepted: examples small no-limits
#

V,A,B = list(map(int, input().strip().split()))
F,C,D = list(map(int, input().strip().split()))

if A+B==2*F and C+D==2*V:
    if B-A==D-C:
        print('IGEN')
    else:
        print('NEM')
else:
    print('NEM')
