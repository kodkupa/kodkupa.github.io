#!/usr/bin/env python3

N, M, R, G, B = map(int, input().strip().split())

transposed = N < M
if (N < M):
    N, M = M, N

grid = [[''] * M for _ in range(N)]

colors = sorted([(R, 'R'), (G, 'G'), (B, 'B')])
pattern = colors[2][1] * colors[2][0] + colors[0][1] * colors[0][0] + colors[1][1] * colors[1][0]
k = 0
for i in range(N):
    for j in range(M):
        if ((i + j) % 2 == 0):
            grid[i][j] = pattern[k]
            k += 1
for i in range(N):
    for j in range(M):
        if ((i + j) % 2 == 1):
            grid[i][j] = pattern[k]
            k += 1

if colors[2][0] > (N * M + 1) // 2:
    print('NO')
else:
    print('YES')
    if transposed:
        for j in range(M):
            for i in range(N):
                print(grid[i][j], sep='', end='')
            print()
    else:
        for i in range(N):
            print(''.join(grid[i]))

