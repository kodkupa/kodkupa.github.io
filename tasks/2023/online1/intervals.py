#!/usr/bin/env pypy3

# input data
N = int(input().strip())
v = []
for i in range(N):
    a, b = map(int, input().strip().split())
    v.append([b, a])
v.sort()

x = dict()
tot = N
for i in range(N):
    if v[i][1] in x and x[v[i][1]] > 0:
        tot -= 1
        x[v[i][1]] -= 1
    if not v[i][0] in x:
        x[v[i][0]] = 0
    x[v[i][0]] += 1


print(tot)  # print the result
