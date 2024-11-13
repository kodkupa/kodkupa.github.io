#!/usr/bin/env python3
# @check-accepted: *
def main():
    N, M = map(int, input().split())

    if N > M:
        print("-1")
        return

    for i in range(N):
        for j in range(M):
            if j < i:
                print("#", end="")
            else:
                print(".", end="")
        print()


if __name__ == "__main__":
    main()
