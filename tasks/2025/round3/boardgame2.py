#!/usr/bin/env python3
# @check-accepted: *

import sys
sys.setrecursionlimit(10**6)
input = sys.stdin.readline
 
INF = 10**18

# Global variables
top = []
g = g = [[] for _ in range(200000 + 1)]
memo = {}

def dfs(x):
    if x in memo:
        return memo[x]

    winning = False
    ret = 0

    for neighbor, weight in g[x]:
        cur_winning, cur_ret = dfs(neighbor)

        if not winning:
            if cur_winning:
                ret = max(ret, cur_ret)
            else:
                winning = True
                ret = weight + cur_ret
        else:
            if not cur_winning:
                ret = min(ret, weight + cur_ret)

    memo[x] = (winning, ret)
    return memo[x]

def solv():
    n, m = map(int,input().split())
    for _ in range(m):
        x, y, z = map(int,input().split())
        g[x].append((y, z))

    ret_winning, ret_value = dfs(1)

    if ret_winning:
        print("Alice")
    else:
        print("Bob")
    print(ret_value)

solv()
