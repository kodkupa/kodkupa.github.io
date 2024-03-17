#!/usr/bin/env python3
# @check-accepted: examples Rsmall NXRsmall no-limits
# O(NlogN) with maxHEAP 

from heapq import heappush, heappop

def solv():
    N = int(input().strip())
    X = list(map(int, input().split()))
    R = list(map(int, input().split()))
    
    squares=[]
    for i in range(N):
        squares.append((X[i]-R[i],R[i],1))
        squares.append((X[i]+R[i],R[i],-1))

    squares.sort()
    #print(squares)

    heap=[]
    toremove={}
    res=0

    for (x,r,ii) in squares:
        if heap:
            while heap[0] in toremove:
                if toremove[heap[0]]==1:
                    toremove.pop(heap[0])
                    heappop(heap)
                else:
                    toremove[heap[0]]-=1
                    heappop(heap)
                if len(heap)==0:
                    break
            if ii==1:
                if heap:
                    res+=(x-last)*(-heap[0])
                last=x
                heappush(heap,-r)
            else:
                res+=(x-last)*(-heap[0])
                last=x
                if heap[0]==-r:
                    heappop(heap)
                else:
                    try: toremove[-r]+=1
                    except: toremove[-r]=1
                
                    
        else:
            heappush(heap,-r)
            last=x
    
    print(2*res)

solv()
