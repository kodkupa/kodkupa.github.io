#!/usr/bin/env python3
# @check-accepted: *

abc = list(map(chr, range(ord('a'), ord('z')+1)))

def solv():
    string = input()
    if len(string) > 3*26:
        return -1
    for char in abc:
        c = string.count(char)
        if c > 3:
            return -1
        if c > 1 and string.count(2*char) != 1:
            return -1
    res = []
    i = 0
    while i < len(string):
        if i+1 < len(string):
            if string[i]==string[i+1]:
                res.append(2*string[i])
                i += 2
            else:
                res.append(string[i])
                i += 1
        else:
            res.append(string[i])
            i += 1
    return ' '.join(res)

for _ in range(int(input())):
    print(solv())
