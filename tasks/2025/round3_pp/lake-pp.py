#!/usr/bin/env python3
# @check-accepted: *

N, M = map(int, input().split())
city = [input() for _ in range(N)]

P = 0
for x in range(N - 1):
    for y in range(M - 1):
        for dx, dy in zip([0, 1], [1, 0]):
            P += int(city[x + dx][y + dy] != city[x][y])

print(P)
