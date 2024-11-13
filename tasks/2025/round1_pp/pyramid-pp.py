#!/usr/bin/env python3
# @check-accepted: examples N<=5 N<=1000 no-limits

import sys

# uncomment the two following lines if you want to read/write from files
# sys.stdin = open('input.txt')
# sys.stdout = open('output.txt', 'w')

N = int(input().strip())

L = -1
i = 1
tot = 0
while tot <= N:
    tot += i * i
    L += 1
    i += 1


print(L)

sys.stdout.close()
