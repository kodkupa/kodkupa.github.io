#!/usr/bin/env python3
# passes: *


def solv():
    N, M = map(int, input().split())
    T = list(map(int, input().strip().split()))
    P = list(map(int, input().strip().split()))

    best = 0
    for i in range(1, N):
        if P[best]*T[i] < P[i]*T[best]:  # P[best]/T[best] < P[i]/T[i]:
            best = i

    res = 0
    if M > 5000:
        k = (M-5000)//T[best]
        res += k*P[best]
        M -= k*T[best]

    dp = [0]*(M+1)
    for i in range(1, M+1):
        for j in range(N):
            if T[j] <= i:
                dp[i] = max(dp[i], dp[i-T[j]]+P[j])
    print(res+max(dp))


solv()
