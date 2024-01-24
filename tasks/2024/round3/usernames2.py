#!/usr/bin/env python3
# @check-accepted: *


S = input().strip()

N = int(input().strip())

U = set(input().strip() for i in range(N))

for i in range(N + 1):
    T = f"{S}{i}" if i != 0 else S
    if T not in U:
        print(T)
        break
