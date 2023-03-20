#!/usr/bin/env python3

# @check-accepted: examples no-limits

def move(amount, from_, to):
    print(amount, from_, to)

n = int(input())

for i in range((n + 1) // 2):
    move(1, 0, 1)
move(n // 2, 0, 1)
for i in range(n // 2):
    move(1, 1, 0)
move(n // 2, 0, 1)
