#!/usr/bin/env python3
# To determine the winner, we need to compare the sums of the two lists.
# To find the owner of the fastest lap, we need to compare the minimums of the two lists.


# input data
n = int(input().strip())
h = list(map(int, input().strip().split()))
v = list(map(int, input().strip().split()))

print("Hamilton" if sum(h) < sum(v) else "Verstappen")
print("Hamilton" if min(h) < min(v) else "Verstappen")

