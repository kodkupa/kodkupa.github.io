#!/usr/bin/env python3
# @check-accepted: examples NQsmall Qsmall Bsmall full
import sys
input = sys.stdin.readline
B = 20

n, q = map(int, input().split())

v = list(map(int, input().split()))

masks = [0] * (1 << B)
for i in range(n):
    masks[v[i]] = v[i]

# Populate the masks array
for i in range((1 << B) - 1, 0, -1):
    b = (i & -i).bit_length() - 1  # equivalent to __builtin_ctz in Python
    masks[i ^ (1 << b)] |= masks[i]
    masks[1 << b] |= masks[i]

masks[0] = 0
for i in range(1, 1 << B):
    b = (i & -i).bit_length() - 1
    masks[i] |= masks[i ^ (1 << b)]
    masks[i] |= masks[1 << b]

results = []
for _ in range(q):
    # Read each query
    x, y = map(int, input().split())
    x = v[x - 1]
    y = v[y - 1]
    ans = 1

    # Process the query
    while (x & y) == 0 and masks[x] != x:
        x = masks[x]
        ans += 1

    results.append(str(-1 if (x & y) == 0 else ans))

print("\n".join(results))
