#!/usr/bin/env python3
# @check-accepted: examples ReallySmall NxK NsqrtN O1

def solve_fast(n, k, l):  # true if Alice wins
    cnt = (n + (l - 1)) // l + n // l  # # of i<=n, i=0,1 mod l
    if n % l == 0 or n % l == 1:
        return cnt % k == 0
    else:
        return cnt % k == 0 or (cnt + 1) % k == 0
    
T = int(input().strip())
for test in range(1, T+1):
    N, K = map(int, input().strip().split())

    S = "Alice" if solve_fast(N, K, K + 1) else "Bob"

    print(S)
