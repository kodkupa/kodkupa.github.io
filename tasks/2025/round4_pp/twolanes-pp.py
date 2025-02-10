#!/usr/bin/env python3
# @check-accepted: examples N<=15 lane1=lane2 oneObstacle no-limits
# NOTE: it is recommended to use this even if you don't understand the following code.

import sys

# uncomment the two following lines if you want to read/write from files
# sys.stdin = open('input.txt')
# sys.stdout = open('output.txt', 'w')

N = int(input().strip())

lane1 = input().strip()
lane2 = input().strip()
ans = 0

for i in range(N):
    if lane1[i] == 'R' and lane2[i] == 'R':
        break
    ans += 1
print(ans)

sys.stdout.close()
