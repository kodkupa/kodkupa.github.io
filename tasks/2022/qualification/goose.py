'''
Minden kockara szimulaljuk a jatekot. 
Az i-edik kockaval dobva egy kor soran eloszor i-t lepunk, majd addig ugralunk elore, amig az alabbi ket feltetel mindegyike teljesul:
1. Nem ertunk a palya vegere.
2. Az ugrani kivant hossz pozitiv (azaz nem 0).
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