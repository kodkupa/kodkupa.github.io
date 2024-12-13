#!/usr/bin/env python3
# @check-accepted: examples K1 N3 no-limits

def main():
    # Input reading
    N, M, L, K = map(int, input().split())
    
    # Check invalid conditions
    if (L % 3 and K != 0) or K > (N - L + 1) * (M - L + 1):
        print("NO")
        return
    
    print("YES")
    
    if K == 0:
        for _ in range(N):
            print('R' * M)
        return
    
    col = "RGB"
    ans = [['R'] * M for _ in range(N)]
    
    for i in range(N):
        for j in range(M):
            ans[i][j] = col[(i + j) % 3]
    
    boundarx = L - 1 + K // (M - L + 1)
    boundary = L - 1 + K % (M - L + 1)
    w = col[(boundarx + boundary + 1) % 3]
    
    if boundarx < N:
        for i in range(boundary, M):
            ans[boundarx][i] = w
        for i in range(boundarx + 1, N):
            for j in range(M):
                ans[i][j] = w
    
    for row in ans:
        print(''.join(row))

if __name__ == "__main__":
    main()
