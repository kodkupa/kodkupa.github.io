#!/usr/bin/env python3
# not passes even with pypy ...

from sys import stdin, stdout
input = stdin.readline
    
def solv():    
    n, q = map(int,input().split())

    bk = 600  # bucket size

    differences = [0] * (n + 1)
    groups = [0] * (1 + (n + 1) // bk)
    frq = [0] * (n + 1)

    differences[0] = groups[0] = (n - 1) * n // 2

    cntdistinct = 1
    distinct = [0] * (bk + bk)
    distinct[1] = 1
    frq[1] = n

    for _ in range(q):
        tp, *R = map(int,input().split())
        if tp == 1:
            a, b = R
            apb = a + b
            frq[a] -= 1
            for pos in range(1, cntdistinct + 1):
                abs_diff = abs(a - distinct[pos])
                differences[abs_diff] -= frq[distinct[pos]]
                groups[abs_diff // bk] -= frq[distinct[pos]]

            frq[b] -= 1
            for pos in range(1, cntdistinct + 1):
                abs_diff = abs(b - distinct[pos])
                differences[abs_diff] -= frq[distinct[pos]]
                groups[abs_diff // bk] -= frq[distinct[pos]]

            for pos in range(1, cntdistinct + 1):
                abs_diff = abs((apb) - distinct[pos])
                differences[abs_diff] += frq[distinct[pos]]
                groups[abs_diff // bk] += frq[distinct[pos]]

            found = False
            for pos in range(1, cntdistinct + 1):
                if distinct[pos] == apb:
                    found = True
                    break

            if not found:
                cntdistinct += 1
                distinct[cntdistinct] = apb

            frq[apb] += 1

            for pos in range(cntdistinct, 0, -1):
                if frq[distinct[pos]] == 0:
                    for x in range(pos, cntdistinct):
                        distinct[x] = distinct[x + 1]
                    cntdistinct -= 1

        else:
            k = R[0]
            for i in range(n // bk + 1):
                if k - groups[i] > 0:
                    k -= groups[i]
                else:
                    for pos in range(i * bk, len(differences)):
                        k -= differences[pos]
                        if k <= 0:
                            #print(pos)
                            stdout.write(str(pos)+'\n') 
                            break
                    break

solv()
