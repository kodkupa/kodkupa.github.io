#!/usr/bin/env python3
# NOTE: it is recommended to use this even if you don't understand the following code.


# input data
n = int(input().strip())
s = input().strip()
q = int(input().strip())

def check(l, r, d):
    for i in range(l, r - d + 1):
        if s[i] != s[i + d]:
            return False
    return True

for _ in range(q):
    l, r = [int(val) for val in input().strip().split()]

    length = r - l + 1
    d = 1
    ok = False
    while d * d <= length and not ok:
        if length % d == 0:
            if check(l, r, d) or d > 1 and check(l, r, length // d):
                ok = True
        d += 1
    
    print("YES" if ok else "NO")  # print the result
