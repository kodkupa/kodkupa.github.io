#!/usr/bin/env python3
# @check-accepted: *

def solv():
    n, k = map(int, input().split())
    C = list(map(int, input().split()))

    max_val = max(C)
    total_sum = sum(C)

    skip = max(0, (k - 5) // (n - 1) - 5)
    k -= skip * (n - 1)
    M = skip * (total_sum - max_val)

    a = C[0]
    b = C[1]

    i = 0
    while True:
        if k == 0:
            break
        if a > b:
            a, b = b, a
        M += a
        C[i] = a
        a = C[(i + 2) % n]
        k -= 1
        i += 1
        i %= n

    print(M)

solv()
