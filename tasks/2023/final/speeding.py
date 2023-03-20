#!/usr/bin/env python3
# sorting + two pointers
# @check-accepted: *

n = int(input().strip())
a = list(map(int, input().strip().split()))
b = list(map(int, input().strip().split()))

mod = int(1e9) + 7
sol = 1
j = -1
a = sorted(a)
b = sorted(b)

for i in range(n):
    while j + 1 < n and b[j + 1] <= a[i]:
        j = j + 1
    sol = (sol * max(0, j + 1 - i)) % mod

print(sol)
