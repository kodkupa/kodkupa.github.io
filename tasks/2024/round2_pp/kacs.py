#!/usr/bin/env python3
# @check-accepted: examples Teljes
# insert brief description of the solution here


# input data

# insert your code here
N =  int(input())

T = list(map(int, input().split()))
ans=0
for t in T:
 	if t >= 1982:
    		ans+=1
print(ans)
