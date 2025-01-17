#!/usr/bin/env python3
# @check-accepted: *

import sys

As, At, Au = map(int, input().strip().split())
Bs, Bt, Bu = map(int, input().strip().split())

D = abs(As - Bs) + abs(At - Bt) + abs(Au - Bu)
print(D)
