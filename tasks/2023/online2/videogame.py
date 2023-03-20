#!/usr/bin/env python3
# insert brief description of the solution here


# input data
T = int(input().strip())
N = int(input().strip())
V = []
for _ in range(N):
    L = list(map(int, input().strip().split()))
    V.append((L[0],1))
    V.append((L[1],3))
M = int(input().strip())
for _ in range(M):
    L = list(map(int, input().strip().split()))
    V.append((L[0],2))
    V.append((L[1],4))
    
ans = 0
first = False
second = False
lf = 0
ls = 0

V = sorted(V)

for i in range(N+M+N+M):
	if V[i][1] == 1:
		first = True
		lf = V[i][0]
	if V[i][1] == 2:
		second = True
		ls = V[i][0]
	if lf + T < ls:
            first = False
	if V[i][1] == 3:
		if not first:
			continue
		first = False
		if second:
			ans += V[i][0] - max(lf,ls) + 1
	if V[i][1] == 4:
		second = False
		if first:
			ans += V[i][0] - max(lf,ls) + 1
			lf = V[i][0] + 1
		
print(ans)  # print the result
