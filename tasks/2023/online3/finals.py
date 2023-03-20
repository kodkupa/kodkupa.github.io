#!/usr/bin/env python3
# @check-accepted: examples S_12=0 nolimits
# insert brief description of the solution here


# input data
N, P = map(int, input().strip().split())
S = [0] + [P * 100 for _ in range(N - 1)]
for i in range(N):
    S[i] += sum(map(int, input().strip().split()))

ans = max(max(S[1:]) - S[0] + 1, 0)
assert 0 <= ans <= P * 100
print(ans)
