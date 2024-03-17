#!/usr/bin/env python3
# @check-accepted: examples N<=20 no-limits
def solve():
    N, M = map(int, input().split())
    line = [input().strip() for _ in range(N)]
    ones = []
    for i in range(N):
        one = [j for j in range(M) if line[i][j] == '1']
        for j in range(1, len(one)):
            if one[j] != one[j - 1] + 1:
                print(0)
                return
        if one:
            ones.append((i, one[0], len(one)))
    if not ones:
        print(0)
        return
    for i in range(1, len(ones)):
        r, c, l = ones[i]
        r1, c1, l1 = ones[i - 1]
        if c1 != c or l1 != l or r != r1 + 1:
            print(0)
            return
    print(1)

T = int(input().strip())
for _ in range(T):
    solve()
