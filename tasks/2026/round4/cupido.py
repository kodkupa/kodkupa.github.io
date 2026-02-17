#!/usr/bin/env python3

from collections import defaultdict

def main():
    import sys
    input = sys.stdin.readline

    N = int(input())
    likes = defaultdict(set)

    for _ in range(N):
        id_, a, b, c = map(int, input().split())
        likes[id_].update([a, b, c])

    mutual = 0
    for id_, liked in likes.items():
        for l in liked:
            if l in likes and id_ in likes[l]:
                mutual += 1

    print(mutual // 2)

if __name__ == "__main__":
    main()
