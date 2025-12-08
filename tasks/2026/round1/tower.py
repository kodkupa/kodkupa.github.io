#!/usr/bin/env pypy3
# insert brief description of the solution here

M = 998244353
# input data
N,S = map(int,input().strip().split())
V = list(map(int, input().strip().split()))

k = [0 for _ in range(S + 1)]
k[0] = 1

def add(x):
    for i in range(S, x-1, -1):
        k[i] = (k[i] + k[i - x]) % M

def rem(x):
    for i in range(x, S + 1):
        k[i] = (k[i] - k[i - x]) % M

for x in V:
    add(x)

for x in V:
    rem(x)
    print("YES" if k[S] == 0 else "NO")
    add(x)
