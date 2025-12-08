#!/usr/bin/env python3
# @check-accepted: examples N<=30 N<=300 no-limits

import sys

def solve():
    N, M = map(int, sys.stdin.readline().split())

    L = (N // 3) + ((N + 1) // 3) + 1

    if M > L:
        print("filippo")
    elif M < L:
        print("tommaso")
    else:
        print("draw")

def main():
    T = int(sys.stdin.readline())
    for _ in range(T):
        solve()

if __name__ == "__main__":
    main()
