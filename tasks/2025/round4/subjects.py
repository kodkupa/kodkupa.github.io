#!/usr/bin/env python3
# @check-accepted: *

from sys import stdin
input = stdin.readline

def main():
    n, m = map(int, input().split())

    subjects = [[False]*(m+1) for j in range(m+1)]
    for _ in range(n):
        K, *temp = list(map(int, input().split()))

        for j in range(K-1):
            for l in range(j + 1, K):
                subjects[temp[j]][temp[l]] = True
                subjects[temp[l]][temp[j]] = True
    ki = []
    for i in range(1, m + 1):
        for j in range(i + 1, m + 1):
            if not subjects[i][j]:
                ki.append((i, j))

    print(len(ki))
    for i in ki:
        print(i[0], i[1])


if __name__ == "__main__":
    main()
