#!/usr/bin/env python3

import sys


INF = 2_000_000_000


def main():
    data = list(map(int, sys.stdin.read().split()))
    it = iter(data)

    T = next(it)
    out_lines = []

    for _ in range(T):
        n = next(it)
        h = next(it)
        w = next(it)

        xs = [next(it) for _ in range(w)]
        ys1 = [next(it) for _ in range(w)]
        ys2 = [next(it) for _ in range(w)]

        # Build and sort walls, add sentinel
        walls = [(xs[i], ys1[i], ys2[i]) for i in range(w)]
        walls.append((INF, 0, 0))
        walls.sort(key=lambda t: t[0])
        wi = 0

        # DP arrays: min and max vertical speed (angle) at each cell
        min_angle = [[INF] * h for _ in range(n)]
        max_angle = [[-INF] * h for _ in range(n)]

        sy = h // 2
        min_angle[0][sy] = 0
        max_angle[0][sy] = 0

        for x in range(n - 1):
            wx, wy1, wy2 = walls[wi]
            is_wall_col = (x == wx)

            for y in range(h):
                if is_wall_col and (y < wy1 or y > wy2):
                    # This cell is blocked by a wall (no hole here)
                    continue

                vmin = min_angle[x][y]
                vmax = max_angle[x][y]
                if vmin > vmax:
                    # This cell is unreachable
                    continue

                next_x = x + 1
                row_min = min_angle[next_x]
                row_max = max_angle[next_x]

                # Try all possible new speeds: current range +/- 1
                for v in range(vmin - 1, vmax + 2):
                    ny = y + v
                    if 0 <= ny < h:
                        if v < row_min[ny]:
                            row_min[ny] = v
                        if v > row_max[ny]:
                            row_max[ny] = v

            if is_wall_col:
                wi += 1

        last_col_min = min_angle[n - 1]
        last_col_max = max_angle[n - 1]
        possible = any(last_col_min[y] <= last_col_max[y] for y in range(h))
        out_lines.append("YES" if possible else "NO")

    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    main()

