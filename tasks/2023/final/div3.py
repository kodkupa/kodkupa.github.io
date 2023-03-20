#!/usr/bin/env python3
# @check-accepted: *

# biggest result if cnt digits of rem remainder are deleted
def remove(s, cnt, rem):
    i = 0
    while i + 1 < len(s):
        if s[i] % 3 == rem and s[i] < s[i + 1]:
            s = s[: i] + s[i + 1 :]
            cnt -= 1
            if cnt == 0:
                return s
            if i > 0: i -= 1
        else:
            i += 1
    i = len(s) - 1
    while i >= 0:
        if s[i] % 3 == rem:
            s = s[: i] + s[i + 1 :]
            cnt -= 1
            if cnt == 0:
                return s
        i -= 1
    return []

def without_leading_0(s):
    for i in range(len(s)):
        if s[i] > 0:
            return s[i:]
    return []

def solve():
    s = [int(c) for c in input()]
    rem = sum(s) % 3
    if rem == 0:
        print(''.join([str(x) for x in s]))
        return
    one = without_leading_0(remove(s.copy(), 1, rem))
    two = without_leading_0(remove(s.copy(), 2, 3 - rem))
    if len(one) > len(two) or len(one) == len(two) and one > two:
        print(''.join([str(x) for x in one]))
    elif len(two) > 0:
        print(''.join([str(x) for x in two]))
    else:
        print(-1)

N = int(input().strip())
for _ in range(N):
    solve()
