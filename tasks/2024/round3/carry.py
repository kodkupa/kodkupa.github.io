#!/usr/bin/env python3
# @check-accepted: examples quadratic
# @check-time-limit-exceeded: X=Y no-limits

# Constants
MOD = 10**9 + 7
BASE = 2

n = int(input().strip())

# Precompute powers
p = [1]
for i in range(1, n + 1):
    p.append(p[i - 1] * BASE % MOD)

A = input().strip()
B = input().strip()

# Invert bits of B
B = ''.join(['1' if b == '0' else '0' for b in B])

# Hash functions


def get_hash(s):
    n = len(s)
    h = [0] * (n + 1)
    for i in range(n):
        h[i + 1] = (h[i] * BASE + ord(s[i]) - ord('0')) % MOD
    return h


ha = get_hash(A)
hb = get_hash(B)

q = int(input().strip())
result = []

for _ in range(q):
    X, Y, L = map(int, input().split())
    l, r = 0, L
    while l < r:
        m = (l + r) // 2
        if (ha[X + m + 1] - ha[X] * p[m + 1]) % MOD == (hb[Y + m + 1] - hb[Y] * p[m + 1] ) % MOD:
            l = m + 1
        else:
            r = m
    if l == L:
        result.append("1")
    else:
        result.append(B[Y + l])

print(' '.join(result))
