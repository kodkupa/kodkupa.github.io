#!/usr/bin/env python3

from sys import stdin
input = stdin.readline

def distsquare(A,B):
    return (A[0]-B[0])**2 + (A[1]-B[1])**2

def solv():
    corners = [list(map(int, input().split())) for i in range(4)]

    N = int(input())
    K = 0
    for j in range(N):
        point = list(map(int, input().split()))
        count = 0
        for i in range(4):
            cur = [distsquare(corners[i],point),
                   distsquare(point,corners[(i+1)%4]),
                   distsquare(corners[i],corners[(i+1)%4])]
            if cur[0]+cur[1] < cur[2]:
                count += 1
            elif cur[0]+cur[1] == cur[2]:
                count += 10
            else:
                count -= 1
        if count == 0:
            K += 1

    print(K)

solv()
