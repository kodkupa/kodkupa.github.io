#!/usr/bin/env python3

def solv():
    N = int(input().strip())
    line = input().strip()
    intervals = []
    cur = 0
    for ch in line:
        if ch == '.':
            cur += 1
        else:
            if cur:
                intervals.append(cur)
            cur=0
    if cur:
        intervals.append(cur)
    intervals.sort()
    res = len(intervals)
    time = 0
    for i in range(1, len(intervals) + 1):
        time = max(time, i + intervals[-i] // 2)
    print(res, time)
    return

for t in range(int(input().strip())):
    solv()
