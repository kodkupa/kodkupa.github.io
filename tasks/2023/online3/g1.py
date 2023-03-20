#!/usr/bin/env python3
# full score
# @check-accepted: *


n, q = map(int, input().split())
racer = list(map(int, input().split()))
pos = [0] * (n + 1)
cnt = [0] * (n + 1)
for i in range(n):
    pos[racer[i]] = i

maxindex = 1
for i in range(q):
    id = int(input())
    p = pos[id]
    other = racer[p - 1]
    racer[p - 1], racer[p] = racer[p], racer[p - 1]
    pos[id] -= 1
    pos[other] += 1
    cnt[other] += 1
    if cnt[other] > cnt[maxindex] or cnt[other] == cnt[maxindex] and other < maxindex:
        maxindex = other
    # print('\\item $'+ str(racer)+'$')
    # print(cnt)
    print(maxindex)
