#!/usr/bin/env python3
# O(N^2)

def solv():
    N = int(input().strip())
    D = list(map(int, input().strip().split()))
    def res(cur):
        l,r=i-1,i+1
        while l>=0 and r<N:
            if D[r]-D[cur]<D[cur]-D[l]:
                cur=r
                r+=1
            else:
                cur=l
                l-=1
        if l<0:
            return N-1
        else:
            return 0
        return
    for i in range(N):
        print(res(i),end=' ')
    return

solv()

