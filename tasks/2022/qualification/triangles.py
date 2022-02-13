#!/usr/bin/env python3

# Triangles solution

# For the smaller subtasks, we can solve the problem using brute force, fixing
# two or three points and checking how many right triangles we have there.

# For the full solution, we can fix each of the points from the input, and
# count how many points are there with the same x coordinate and same y
# coordinate. In order to compute this fast, we will store using frequency
# arrays how many points we got for each possible x and y coordinate and thus,
# the final complexity would be O(n).

MAXX = 200_005

N = int(input().strip())

X = [0] * N
Y = [0] * N
for i in range(N):
    X[i], Y[i] = map(int, input().strip().split())



cntx = [0] * MAXX
cnty = [0] * MAXX

for i in range(N):
    cntx[X[i]] += 1
    cnty[Y[i]] += 1

ans = 0

for i in range(N):
    cntx[X[i]] -= 1
    cnty[Y[i]] -= 1

    ans += cntx[X[i]] * cnty[Y[i]]

    cntx[X[i]] += 1
    cnty[Y[i]] += 1


print(ans)  # print the result
