'''
Minden kockára szimuláljuk a játékot. 
Az i-edik kockával dobva egy kör során először i-t lépünk, majd addig ugrálunk előre, amíg az alábbi két feltétel mindegyike teljesül:
1. Nem értünk a pálya végére.
2. Az ugrani kívánt hossz pozitív (azaz nem 0).
'''

n = int(input())
j = list(map(int, input().split()))

for i in range(1, 7):
    p, a = 0, 0
    while p < n:
        p += i
        a += 1
        while p < n and j[p] != 0:
            p += j[p]
    print(a, end = ' ')