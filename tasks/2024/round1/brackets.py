#!/usr/bin/pypy3
# @check-accepted: examples NVerysmall NASumSmall no-limits

N = int(input().strip())
A = list(map(int, input().strip().split()))

s = sum(A)
if s%2!=0:
    print(-1)
else:
    vis = [[0 for _ in range(s//2+1)] for _ in range(N+1)]

    vis[0][0]=1
    for i in range(N):
        for j in range(s//2+1):
            if vis[i][j]>0:
                if j+A[i]<=s//2:
                    vis[i+1][j+A[i]] = 1
                if j-A[i]>=0:
                    vis[i+1][j-A[i]] = 2
    
    if vis[N][0]>0:
        ans = []
        ind, sum = N, 0
        while ind>0:
            ans.append(A[ind-1]*('(' if vis[ind][sum]==1 else ')'))
            if vis[ind][sum]==1:
                sum-=A[ind-1]
            else:
                sum+=A[ind-1]
            ind-=1
        print("".join(ans[::-1]))
    else:
        print(-1)
    
