#!/usr/bin/env python3
# NOTE: it is recommended to use this even if you don't understand the following code.

import sys

# uncomment the two following lines if you want to read/write from files
# sys.stdin = open('input.txt')
# sys.stdout = open('output.txt', 'w')

T = int(input().strip())
for test in range(1, T+1):
    N = int(input().strip())
    
    P = list(map(int, input().strip().split()))
    
    points = [0, 25, 18, 15, 12, 10, 8, 6, 4, 2, 1]
    score = 0
    max_score = 0
    for nr in P:
        if nr != 1:
            max_score += 25
        else:
            max_score += 18
        if nr <= 10:
            score += points[nr]    
    
    # INSERT YOUR CODE HERE
    
    
    print("Champion" if score >= max_score else "Practice harder")

sys.stdout.close()
