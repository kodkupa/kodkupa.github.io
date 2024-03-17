#!/usr/bin/env python3
# @check-accepted: Examples A_i>0 N<=100 N<=1000 full

import bisect
from sys import stdin
input=stdin.readline

def solv():
    N, M, K = map(int, input().strip().split())
    A = list(map(int, input().strip().split()))
    B = list(map(int, input().strip().split()))
    preB=[0]*M
    preB[0]=B[0]
    lookupB={B[0]:0}
    for i in range(1,M):
        preB[i]=preB[i-1]+B[i]
        lookupB[preB[i]]=i
    preA=[0]*N
    preA[0]=A[0]
    goodA=[-1]*N
    if preA[0] in lookupB:
        goodA[0]=lookupB[preA[0]]
    for i in range(1,N):
        preA[i]=preA[i-1]+A[i]
        try: goodA[i]=lookupB[preA[i]]
        except: pass
    
    if preA[-1]!=preB[-1]:
        print(-1)
        return

    indexx=0
    while goodA[indexx]==-1:
        indexx+=1
    L=[goodA[indexx]]
    I=[indexx]
    prev={}
    for i in range(indexx+1,N):
        if goodA[i]==-1:
            continue
        index=bisect.bisect_left(L,goodA[i])
        if index>=len(L): #==
            L.append(goodA[i])
            prev[i]=I[-1]
            I.append(i)
        else:
            if L[index]>goodA[i]:
                L[index]=goodA[i]
                if index>0:
                    prev[i]=I[index-1]
                I[index]=i
    if len(L)<K:
        print(-1)
        return
    start=[I[K-2]]
    for i in range(K-1):
        if i!=K-2:
            start.append(prev[start[-1]])
    for i in range(K-2,-1,-1):
        print(start[i]+1,end=' ')
    print()
    for i in range(K-2,-1,-1):
        print(lookupB[preA[start[i]]]+1,end=' ')
    print()
        
solv()
