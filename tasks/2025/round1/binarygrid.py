#!/usr/bin/env python3
# @check-accepted: examples NMsmall N1 Nsmall no-limits

from sys import stdin, stdout

def rd(): return stdin.readline().strip()
def rdl(x): return map(x, rd().split())
def wt(x): stdout.write(str(x))
def wtl(x): wt(str(x) + '\n')

for tt in range(int(rd())):
    rd();
    n, m = rdl(int)
    s = ["" for _ in range(n)]
    for i in range(n):
        s[i] = rd()
    a = [[ord(s[i][j]) - ord('0') for j in range(m)] for i in range(n)]
    inf = 1_000_000_009
    dp_cols = [[inf, inf], [inf, inf]]
    for f1 in range(2):
        for f2 in range(2):
            dp_cols[f1][f2] = f1 + f2
    for i in range(2, n):
        new_dp = [[inf, inf], [inf, inf]]
        for f1 in range(2):
            for f2 in range(2):
                if dp_cols[f1][f2] == inf:
                    continue
                for f3 in range(2):
                    fail = False
                    for j in range(m):
                        if (a[i][j] ^ f3) == (a[i - 1][j] ^ f2) == (a[i - 2][j] ^ f1):
                            fail = True
                            break
                    if not fail:
                        new_dp[f2][f3] = min(new_dp[f2][f3], f3 + dp_cols[f1][f2])
        for f1 in range(2):
            for f2 in range(2):
                dp_cols[f1][f2] = new_dp[f1][f2]
    dp_rows = [[inf, inf], [inf, inf]]
    for f1 in range(2):
        for f2 in range(2):
            dp_rows[f1][f2] = f1 + f2
    for j in range(2, m):
        new_dp = [[inf, inf], [inf, inf]]
        for f1 in range(2):
            for f2 in range(2):
                if dp_rows[f1][f2] == inf:
                    continue
                for f3 in range(2):
                    fail = False
                    for i in range(n):
                        if (a[i][j] ^ f3) == (a[i][j - 1] ^ f2) == (a[i][j - 2] ^ f1):
                            fail = True
                            break
                    if not fail:
                        new_dp[f2][f3] = min(new_dp[f2][f3], f3 + dp_rows[f1][f2])
        for f1 in range(2):
            for f2 in range(2):
                dp_rows[f1][f2] = new_dp[f1][f2]
    x, y = inf, inf
    for f1 in range(2):
        for f2 in range(2):
            x = min(x, dp_cols[f1][f2])
            y = min(y, dp_rows[f1][f2])
    wtl(-1 if x >= inf or y >= inf else x + y)
