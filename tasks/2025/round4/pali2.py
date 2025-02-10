#!/usr/bin/env python3
# should pass with pypy

import sys
input = sys.stdin.readline

# Global constants
b1 = 200017
b2 = 201497
b3 = 202471
m1 = 10**9 + 7
m2 = 998244353
#m3 = 1000004099

# Maximum size (n can be up to 200000 in the worst case)
MAXN = 200001

# Precomputed powers (will be computed in main)
pw = [None] * (MAXN)

class MyHash:
    __slots__ = ('h1', 'h2')
    def __init__(self, h1, h2):
        self.h1 = h1 % m1
        self.h2 = h2 % m2

    def __eq__(self, other):
        return (self.h1 == other.h1 and 
                self.h2 == other.h2)

    def __add__(self, other):
        return MyHash((self.h1 + other.h1) % m1,
                      (self.h2 + other.h2) % m2)

    def __sub__(self, other):
        return MyHash((self.h1 - other.h1 + m1) % m1,
                      (self.h2 - other.h2 + m2) % m2)

    def __mul__(self, other):
        if isinstance(other, MyHash):
            return MyHash((self.h1 * other.h1) % m1,
                          (self.h2 * other.h2) % m2)
        elif isinstance(other, int):
            return MyHash((self.h1 * other) % m1,
                          (self.h2 * other) % m2)
        else:
            raise TypeError("Unsupported type for multiplication")

    def __repr__(self):
        return f"MyHash({self.h1}, {self.h2})"

def add_hash(me, x):
    """
    Given a hash 'me' (of type MyHash) and an integer x,
    return a new MyHash value computed as:
       h1 = (me.h1 * b1 + x) mod m1,
       h2 = (me.h2 * b2 + x) mod m2,
       h3 = (me.h3 * b3 + x) mod m3.
    """
    return MyHash((me.h1 * b1 + x) % m1,
                  (me.h2 * b2 + x) % m2)

def simple(hc, l, r):
    """
    Returns the hash value of the interval [l, r] using the array hc.
    (Assumes 1-indexing and that hc[0] is the identity element.)
    """
    # simple(hc, l, r) = hc[r] - (hc[l-1] * pw[r-l+1])
    return hc[r] - (hc[l-1] * pw[r - l + 1])

def interv(hc, hd, l, r, val):
    """
    Returns simple(hc, l, r) + (simple(hd, l, r) * val)
    """
    return simple(hc, l, r) + (simple(hd, l, r) * val)

def bin1(i, val, n, h, hq, hrev, hqrev):
    """
    Binary search around index i (for odd–length palindromes).
    Searches for the largest d such that for l = i-d, r = i+d (with l>=1 and r<=n)
    we have:
       interv(h, hq, l, r, val) == interv(hrev, hqrev, n - r + 1, n - l + 1, val)
    Returns a tuple (l, r).
    """
    st = 0
    dr = n
    rezl = i
    rezr = i
    while st <= dr:
        mid = (st + dr) // 2
        l = i - mid
        r = i + mid
        if l >= 1 and r <= n:
            if interv(h, hq, l, r, val) == interv(hrev, hqrev, n - r + 1, n - l + 1, val):
                rezl = l
                rezr = r
                st = mid + 1
            else:
                dr = mid - 1
        else:
            dr = mid - 1
    return (rezl, rezr)

def bin2(i, val, n, h, hq, hrev, hqrev):
    """
    Binary search around index i (for even–length palindromes).
    Searches for the largest d such that for l = i-d, r = i+d+1 (with l>=1 and r<=n)
    we have:
       interv(h, hq, l, r, val) == interv(hrev, hqrev, n - r + 1, n - l + 1, val)
    Returns a tuple (l, r).
    """
    st = 0
    dr = n
    # initial values: no valid even palindrome => l > r
    rezl = i + 1
    rezr = i
    while st <= dr:
        mid = (st + dr) // 2
        l = i - mid
        r = i + mid + 1
        if l >= 1 and r <= n:
            if interv(h, hq, l, r, val) == interv(hrev, hqrev, n - r + 1, n - l + 1, val):
                rezl = l
                rezr = r
                st = mid + 1
            else:
                dr = mid - 1
        else:
            dr = mid - 1
    return (rezl, rezr)

def main():
    import sys    
    
    # Precompute pw[0..MAXN-1]
    pw[0] = MyHash(1, 1)
    for i in range(1, MAXN):
        pw[i] = add_hash(pw[i-1], 0)
    
    # Read n and the sequence v[1..n]
    n = int(input())
    # use 1-indexing: index 0 unused.
    v = [0] + list(map(int,input().split()))
    
    ans = 1

    # Build hash arrays h and hq for the original sequence.
    # h[0] and hq[0] are the identity (0-hash)
    h = [MyHash(0, 0)] * (n + 1)
    hq = [MyHash(0, 0)] * (n + 1)
    h[0] = MyHash(0, 0)
    hq[0] = MyHash(0, 0)
    for i in range(1, n + 1):
        if v[i] > 0:
            h[i] = add_hash(h[i-1], v[i])
            hq[i] = add_hash(hq[i-1], 0)
        else:
            h[i] = add_hash(h[i-1], 0)
            hq[i] = add_hash(hq[i-1], 1)

    # Build reversed arrays hrev and hqrev.
    # Create v_rev as the reversed sequence (1-indexed)
    v_rev = [0] * (n + 1)
    for i in range(1, n + 1):
        v_rev[i] = v[n - i + 1]
    hrev = [MyHash(0, 0)] * (n + 1)
    hqrev = [MyHash(0, 0)] * (n + 1)
    hrev[0] = MyHash(0, 0)
    hqrev[0] = MyHash(0, 0)
    for i in range(1, n + 1):
        if v_rev[i] > 0:
            hrev[i] = add_hash(hrev[i-1], v_rev[i])
            hqrev[i] = add_hash(hqrev[i-1], 0)
        else:
            hrev[i] = add_hash(hrev[i-1], 0)
            hqrev[i] = add_hash(hqrev[i-1], 1)

    # For each center i, try odd and even palindromes.
    for i in range(1, n + 1):
        # Odd-length palindrome centered at i.
        p_l, p_r = bin1(i, n + 1, n, h, hq, hrev, hqrev)
        ans = max(ans, p_r - p_l + 1)
        l2 = p_l - 1
        r2 = p_r + 1
        if l2 >= 1 and r2 <= n:
            if v[l2] == -1 or v[r2] == -1:
                p_l2, p_r2 = bin1(i, max(v[l2], v[r2]), n, h, hq, hrev, hqrev)
                ans = max(ans, p_r2 - p_l2 + 1)
        
        # Even-length palindrome centered between i and i+1.
        if i == n:
            continue
        p_l, p_r = bin2(i, n + 1, n, h, hq, hrev, hqrev)
        ans = max(ans, p_r - p_l + 1)
        l2 = p_l - 1
        r2 = p_r + 1
        if l2 >= 1 and r2 <= n:
            if v[l2] == -1 or v[r2] == -1:
                p_l2, p_r2 = bin2(i, max(v[l2], v[r2]), n, h, hq, hrev, hqrev)
                ans = max(ans, p_r2 - p_l2 + 1)
    
    print(ans)

if __name__ == '__main__':
    main()
    
