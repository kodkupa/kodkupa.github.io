#!/usr/bin/env python3
# The solution is brute force, we generate the multiples of K until each digit occurs.
# To check the digits of a number, we repeat taking the remainder by 10 (last digit),
# and dividing the number by 10 (deleting last digit).
# We keep track which digit occurred in a bool list.
# It is easy to prove that there cannot be more than 100 multiples until every digit occurs.
# In fact, the maximum we found is 72 for 125.

def solve(k):
    digits = [False] * 10
    cnt = 0
    ans = 0
    while cnt < 10:
        ans += 1
        x = ans * k
        while x > 0:
            if not digits[x % 10]:
                cnt += 1
                digits[x % 10] = True
            x //= 10
    return ans

# input data
n = int(input())
for i in range(n):
    print(solve(int(input())))

