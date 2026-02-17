#!/usr/bin/env python3
# @check-accepted: *

n = int(input().strip())
ans = 0
milk = 0
food = 0
for i in range(n):
    if milk >= 50:
        ans += 1
        milk -= 50
    elif food >= 80:
        ans += 1
        food -= 80
    f, t = input().split()
    if t == 'M':
        milk += int(f)
    else:
        food += int(f)

print(ans)
