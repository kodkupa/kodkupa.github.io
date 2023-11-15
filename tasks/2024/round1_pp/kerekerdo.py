#!/usr/bin/env python3
# @check-accepted: examples N5 N100 full

n, a, b = list(map(int, input().strip().split()))
fak = (b-a+1 if a<=b else n-(a-b)+1)
print("Tul konnyu!" if fak<5 else fak)
