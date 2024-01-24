#!/usr/bin/env python3
# @check-accepted: examples Nsmall Nmedium Nlarge

input()
s = list(input().strip())

mn, sum = 0, 0
for i in s:
    sum += 1 if i == '(' else -1
    mn = min(mn, sum)

ans = []

l, r = 0, len(s)-1
while l<r and mn < 0:
    if s[l]=='(':
        l += 1
    elif s[r]==')':
        r -= 1
    else:
        assert s[l]==')' and s[r]=='('
        ans.append((l, r))
        s[l], s[r] = s[r], s[l]
        mn+=2

print(len(ans))
print(*[f"{x[0]} {x[1]}" for x in ans], sep='\n')
