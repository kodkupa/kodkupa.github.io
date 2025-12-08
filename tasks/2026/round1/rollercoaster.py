#!/usr/bin/env python3
# @check-accepted: examples NoUpFirstBoost NoUp NoHor AtMostTwoHor no-limits
# insert brief description of the solution here


def sol():
    N = int(input())
    S = input().strip()

    res = 0
    speed = 0
    hor = 0

    for char in S:
        if char == "D":
            speed += 9
        elif char == "U":
            speed -= 11
        elif char == "B":
            speed += 10
        else:
            hor += 1
        while speed <= 0 and hor:
            speed += 10
            hor -= 1
            res += 1
        if speed <= 0:
            return -1

    return res


print(sol())  # print the result
