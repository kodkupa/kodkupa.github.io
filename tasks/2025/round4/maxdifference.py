#!/usr/bin/env python3
# insert brief description of the solution here
T = int(input())
for _ in range(T):
    N = int(input().strip())
    V = list(map(int, input().strip().split()))
    ans = 0
    setMax = -1e9
    setMin = -1e9
    for x in V:
        setMax = max(ans + x, setMax)
        setMin = max(ans - x, setMin)
        ans = max(setMax - x, setMin + x)

    print(ans)
