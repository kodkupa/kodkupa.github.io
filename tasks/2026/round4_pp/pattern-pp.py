#!/usr/bin/env python3

import sys

def main():
    input = sys.stdin.readline

    SMAX = 50
    NMAX = 10**5

    # Point as tuple (x, y), ordering is lexicographic by default in Python
    def normalize_segment(a, b):
        return (a, b) if a <= b else (b, a)

    # Read a segment and normalize endpoints
    def read_segment():
        x1, y1, x2, y2 = map(int, input().split())
        return normalize_segment((x1, y1), (x2, y2))

    # Read pattern
    s = int(input())
    pattern = [None] * (s + 1)
    for i in range(1, s + 1):
        pattern[i] = read_segment()

    # Read drawing segments and insert into set
    n = int(input())
    drawing = [None] * (n + 1)
    ds = set()
    for i in range(1, n + 1):
        seg = read_segment()
        drawing[i] = seg
        ds.add(seg)

    ans = 0

    # Try aligning pattern[1] with every drawing segment
    for i in range(1, n + 1):
        (p1, p2) = pattern[1]
        (d1, d2) = drawing[i]

        dx = d1[0] - p1[0]
        dy = d1[1] - p1[1]

        # Check second endpoint of first segment
        nx = p2[0] + dx
        ny = p2[1] + dy
        ok = (d2 == (nx, ny))

        # Check all other pattern segments
        j = 2
        while ok and j <= s:
            (a1, a2) = pattern[j]

            nx1 = a1[0] + dx
            ny1 = a1[1] + dy
            nx2 = a2[0] + dx
            ny2 = a2[1] + dy

            to_check = normalize_segment((nx1, ny1), (nx2, ny2))
            ok = (to_check in ds)
            j += 1

        if ok:
            ans += 1

    print(ans)


if __name__ == "__main__":
    main()
