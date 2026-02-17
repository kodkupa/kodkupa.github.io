#!/usr/bin/env python3
# @check-accepted: examples hardcode naive c1dp c2dp
# @check-time-limit-exceeded: fixcorner full

from sys import stdin, stdout

def rd(): return stdin.readline().strip()
def rdl(x): return map(x, rd().split())
def wt(x): stdout.write(str(x))
def wtl(x): wt(str(x) + '\n')

n, m = rdl(int)
a = [list(rdl(int)) for i in range(n)]
c = [list(rdl(int)) for i in range(n)]

cs = set()
for i in range(n):
  for j in range(m):
    cs.add(c[i][j])
res, inf = a[0][0], 3 * 10**18 + 9
dp = [[-inf for j in range(m)] for i in range(n)]
for col in cs:
  for i in range(n):
    for j in range(m):
      dp[i][j] = max(a[i][j] if c[i][j] == col else -inf, a[i][j] + max(dp[i - 1][j] if i > 0 else -inf, dp[i][j - 1] if j > 0 else -inf))
      if c[i][j] == col:
        res = max(res, dp[i][j])

wtl(res)
