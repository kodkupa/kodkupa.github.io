#!/usr/bin/env python3
# Snow White rides down once with as many dwarfs as fit next to her,
# the others go down in groups of W // D; k rides down need 2k - 1 rides.


# input data
W = int(input())
S = int(input())
D = int(input())

with_sw = min((W - S) // D, 7)
per_ride = W // D
rest = 7 - with_sw
down = 1 + (rest + per_ride - 1) // per_ride

print(2 * down - 1)  # print the result
