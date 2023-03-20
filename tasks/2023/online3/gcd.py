#!/usr/bin/env python3
# full score
# @check-accepted: *

def digits(x):
    return len(str(x))

# input data
n = int(input().strip())
d = int(input().strip())

a = d
while digits(a) < n:
    a *= 2
b = a + d
if digits(b) == n:
    print(a, b)
else:
    b = a - d
    if b > 0 and digits(b) == n:
        print(a, b)
    else:
        print(0, 0)

