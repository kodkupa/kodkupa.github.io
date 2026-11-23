#!/usr/bin/env python3
# Full solution: a double d-d scores 100 + d, any other roll 10 * smaller + larger.

def score(x, y):
    if x == y:
        return 100 + x
    return 10 * min(x, y) + max(x, y)

N = int(input())

W1 = W2 = X = 0
for _ in range(N):
    A, B, C, D = map(int, input().split())
    s1, s2 = score(A, B), score(C, D)
    if s1 > s2:
        W1 += 1
    elif s2 > s1:
        W2 += 1
    else:
        X += 1

print(W1, W2, X)  # print the result
