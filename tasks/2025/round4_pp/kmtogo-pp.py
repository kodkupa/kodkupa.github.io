#!/usr/bin/env python3
# @check-accepted: *
# brute force O(NlogN)

N = int(input())
digit_count = [0] * 10
for i in range(1, N + 1):
    while i:
        digit_count[i % 10] += 1
        i //= 10

print(*digit_count)  # print the result
