#!/usr/bin/env python3

t = int(input())
for _ in range(t):
    n = int(input())
    v = list(map(int, input().strip().split()))
    v[0] = 0
    v[-1] = 0
    for i in range(1, n+2):
        v[i] += v[i-1]

    sum = 0
    mh = 0
    debt = 0

    for i in range(1, n+1):
        debt += mh - v[i]
        debt = max(debt, 0)
        sum += v[i]
        mh = max(mh, (sum + i)//(i + 1))

    if debt > 0:
        print("NO")
    else:
        print("YES")
