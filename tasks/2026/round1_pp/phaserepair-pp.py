#!/usr/bin/env python3
# @check-accepted: examples trivial small few-distinct structured no-limits
import sys
data = sys.stdin.read().strip().split()
it = iter(data)
N = int(next(it)); M = int(next(it))
a = [int(next(it)) for _ in range(N)]
if M==1:
    print(0); print()
    sys.exit()
occ = [0]*M
for x in a: occ[x]=1
K = sum(occ)
if K<=1:
    print(0); print()
    sys.exit()
P = [r for r in range(M) if occ[r]]
best_gap=-1; best_j=0
for j in range(len(P)):
    cur=P[j]; nxt=P[(j+1)%len(P)]
    diff = nxt-cur
    if diff<=0: diff+=M
    gap = diff-1
    if gap>best_gap:
        best_gap=gap; best_j=j
L = best_gap
B = M-1-L
start = P[(best_j+1)%K]
print(B)
if B>0:
    seq = [(start+k)%M for k in range(B)]
    print(" ".join(map(str,seq)))
else:
    print()
