#!/usr/bin/env python3
# @check-accepted: examples Teljes
# insert brief description of the solution here


# input data

# insert your code here
N =  int(input())

T = list(map(int, input().split()))
ans=-1
for i in range(0,N):
 	if T[i] == 7:
    		ans=(i+1)
    		break
print(ans)
