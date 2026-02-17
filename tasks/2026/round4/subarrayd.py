#!/usr/bin/env python3

N, K = map(int, input().split())
V = list(map(int, input().split()))

def check(x):
    sum1 = 0
    ans = 0
    for i in V:
        sum1 += i
        if sum1 < i: sum1 = i
        if sum1 > x:
            ans += sum1 - x
            sum1 = x
        if ans > 10**9: return 10**9 + 1
    return ans


st = -10**16
dr = 10**16
best = 0
while st <= dr:
    mid = (st + dr) // 2
    if check(mid) <= K:
        dr = mid - 1
        best = mid
    else:
        st = mid + 1

best = int(best)
print(best)