#!/usr/bin/env pypy3
# @check-accepted: examples bruteforce quadratic 
# @check-time-limit-exceeded: all

def can(digit, prec, count_prec, sum):
    if digit == 1 and sum == prec and count_prec == 2:
        return False
    mi = 0
    cur = 0
    if prec == 0:
        cur = count_prec
    for i in range(digit):
        if cur == 2:
            mi += 1
            cur = 0
        elif cur == 1:
            cur += 1
        else:
            mi += (digit - i) // 3
            break
    ma = 0
    cur = 0
    if prec == 9:
        cur = count_prec
    for i in range(digit):
        if cur == 2:
            ma += 8
            cur = 0
        elif cur == 1:
            ma += 9
            cur += 1
        else:
            ma += 9 * (digit - i) - (digit - i) // 3
            break
    return sum >= mi and sum <= ma


# input data
def solve():
    N, S = input().strip().split()
    N = int(N)
    add = max(0, N//8-len(S))+2
    S = '0'*add+S
    stop = -1
    tot = 0
    cur_S = ""
    for i in range(add, len(S)):
        tot += int(S[i])
        if S[i] == S[i-1] and S[i] == S[i-2]:
            stop = i
            cur_S = S[:i+1]
            break
    if stop == -1 and tot == N:
        for h in range(len(S)):
            if S[h] != '0':
                print(S[h:])
                return
        return

    if stop == -1:
        stop = len(S)-1
        cur_S = S
    for i in range(stop, -1, -1):
        # print(i)
        for j in range(int(cur_S[i])+1, 10):
            cur_S = cur_S[:i]+str(j)
            tot += 1
            if i > 1 and cur_S[i] == cur_S[i-1] and cur_S[i] == cur_S[i-2]:
                continue
            count_prec = 1
            if i > 0 and cur_S[i] == cur_S[i-1]:
                count_prec += 1
            # print(cur_S, len(S)-i-1, count_prec, tot, N-tot)
            if can(len(S)-i-1, j, count_prec, N-tot):
                for h in range(len(S)-i-1):
                    for k in range(10):
                        cur_S = cur_S+str(k)
                        if len(cur_S) > 2 and cur_S[-1] == cur_S[-2] and cur_S[-1] == cur_S[-3]:
                            cur_S = cur_S[:-1]
                            continue
                        count_prec = 1
                        if len(cur_S) > 1 and cur_S[-1] == cur_S[-2]:
                            count_prec += 1
                        if can(len(S)-len(cur_S), k, count_prec, N-tot-k):
                            tot += k
                            break
                        else:
                            cur_S = cur_S[:-1]
                for h in range(len(cur_S)):
                    if cur_S[h] != '0':
                        print(cur_S[h:])
                        return
        tot -= int(cur_S[i])
    print(-1)


T = int(input().strip())
for _ in range(T):
    solve()
