#!/usr/bin/env python3
# constructive

def solv(a,b):
    #3:
    if a==33 and b<=30:
        print(11,b//3)
        b-=b//3
        print(11,b//2)
        b-=b//2
        print(11,b)
        return
    #4:
    if 33<=a<=43 and 11<=b<=41:
        b-=11
        print(a-33,11)
        print(11,b//3)
        b-=b//3
        print(11,b//2)
        b-=b//2
        print(11,b)
        return
    #5:
    if 33<=a<=53 and 22<=b<=52:
        a-=33
        b-=22
        print(a//2,11)
        a-=a//2
        print(a,11)
        print(11,b//3)
        b-=b//3
        print(11,b//2)
        b-=b//2
        print(11,b)
        return
    print('-1 -1')
    return

t = int(input().strip())
for i in range(t):
    a,b = list(map(int, input().strip().split()))
    solv(a,b)
    
