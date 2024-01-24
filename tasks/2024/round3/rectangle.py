#!/usr/bin/env python3
# @check-accepted: *

# Model solution: sort lengths decreasing and search for
# first two pairs of consecutive equal elements


# input data
n = int(input().strip())
s = list(map(int, input().strip().split()))

s.sort(reverse=True)
a = 0
b = 0
i = 1
while i < len(s):
    if s[i] == s[i - 1]:
        if a == 0:
            a = s[i]
            i += 1
        elif b == 0:
            b = s[i]
            break
    i += 1

print(a * b)  # print the result
