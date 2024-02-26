#!/usr/bin/env python3
# @check-accepted: examples Nsmall no-limits
from sys import stdin, stdout

def rd(): return stdin.readline().strip()
def rdl(x): return map(x, rd().split())
def wt(x): stdout.write(str(x))
def wtl(x): wt(str(x) + '\n')

n = int(rd())
p = list(rdl(int));
pos = p.index(1)
for i in range(n):
  if p[(pos + i) % n] != i + 1:
    wtl(-1)
    exit()
wtl((n - pos) % n)
