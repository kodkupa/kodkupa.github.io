#!/usr/bin/env python3
# @check-accepted: examples small_T k_equals_1 full

import sys

def main():
    line = sys.stdin.readline().split()
    N = int(line[0])
    T = int(line[1])
    K = int(line[2])
    
    a = list(map(int, sys.stdin.readline().split()))
    
    # Compute need = ceil(67*N/100)
    need = (67 * N + 99) // 100
    
    streak = 0
    for i in range(T):
        if a[i] >= need:
            streak += 1
        else:
            streak = 0
        
        if streak == K:
            print(i - K + 2)  # 1-based index
            return
    
    print(-1)

if __name__ == "__main__":
    main()
