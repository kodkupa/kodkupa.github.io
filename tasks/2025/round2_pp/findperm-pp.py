#!/usr/bin/env python3
# check-accepted: *
import sys
def ask(a, b):
    print(f"? {a} {b}", flush=True)
    ans = int(input())
    return ans

def main():
    n = int(input())
    msb = [0] * (n + 1)
    sol = [0] * (n + 1)
    
    maxim = 0
    for i in range(1, n + 1):
        x = ask(i, i)
        msb[i] = x
        maxim = max(maxim, msb[i])
    
    for bit in range(maxim + 1):
        who = 0
        for i in range(1, n + 1):
            if msb[i] == bit:
                who = i
                break
        for i in range(1, n + 1):
            x = ask(who, i)
            if x == bit:
                sol[i] += (1 << bit)
    
    print("! ", end="")
    for i in range(1, n + 1):
        print(sol[i], end=" ")
    print()

if __name__ == "__main__":
    main()
