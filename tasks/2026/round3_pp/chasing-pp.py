#!/usr/bin/env python3
# @check-accepted: *

import math

Dx, Dy, Ds = map(float, input().strip().split())
Bx, By, Bs = map(float, input().strip().split())
dir = input().strip()

if dir == 'U' or dir == 'D':
    Dx, Dy = Dy, Dx
    Bx, By = By, Bx
    dir = 'R' if dir == 'U' else 'L'
if dir == 'L':
    Dx = -Dx
    Bx = -Bx
    dir = 'R'

T1 = abs(Dy - By) / Ds
assert T1 >= 0
Bx += Bs * T1

if Bx > Dx and Ds <= Bs:
    print(-1)
    exit(0)

T2 = (Bx - Dx) / (Ds - Bs) if Bx > Dx else (Dx - Bx) / (Ds + Bs)
assert T2 >= 0
print(math.ceil(T1 + T2))
