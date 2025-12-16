#!/usr/bin/env python3
# @check-accepted: examples NMsmall RD no-limits


def main():
    N, M, K = map(int, input().split())
    P = input().strip()

    free_cells = N * M - 1
    vis = [[False] * M for _ in range(N)]
    vis[0][0] = True

    x, y = 0, 0

    for i, c in enumerate(P):
        if c == "R":
            y += 1
        elif c == "L":
            y -= 1
        elif c == "U":
            x -= 1
        elif c == "D":
            x += 1

        if not vis[x][y]:
            vis[x][y] = True
            free_cells -= 1

        if free_cells == K - 1:
            print(i)
            return

    print(len(P))


if __name__ == "__main__":
    main()
