#!/usr/bin/env python3
# @check-accepted: *

n, x = map(int, input().split())
l = list(map(int, input().strip().split()))

l.sort()
t = 0
i = 0
while True:
    if i + 1 < n and l[i] + l[i + 1] <= x:
        i += 2
    elif i < n and l[i] <= x:
        i += 1
    else:
        break
    t += 1

print(t)
