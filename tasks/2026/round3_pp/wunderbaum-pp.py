#!/usr/bin/env python3
# @check-accepted: examples NsmallnoL Nsmall Nmid no-limits
# insert brief description of the solution here


L, N = map(int, input().split())



L += 12*(N//6)
N %= 6
L += [0, 1, 3, 6, 8, 9][N]

print(L)
