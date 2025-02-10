#!/usr/bin/env python3
# should pass with pypy

from sys import stdin, stdout

def rd(): return stdin.readline().strip()
def rdl(x): return map(x, rd().split())
def wt(x): stdout.write(str(x))
def wtl(x): wt(str(x) + '\n')

n, m, q = rdl(int)
a, b, d = [0 for i in range(n)], [0 for i in range(n)], [2 * 10**18 for i in range(1 << n)]
for i in range(n):
  a[i], b[i] = rdl(int)

for i in range(m):
  rd()
  v = list(rdl(int))
  d[sum(2**x for x in v)] = 0

for i in range(n):
  for j in range(1 << n):
    d[j ^ (1 << i)] = min(d[j ^ (1 << i)], d[j] + (b[i] if (j >> i) & 1 else a[i]))

for i in range(q):
  rd()
  v = list(rdl(int))
  wtl(d[sum(2**x for x in v)])
