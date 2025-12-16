#!/usr/bin/env python3

import sys

MOD = 998244353

def mat_mul(A, B):
    """3x3 matrix multiplication (A * B) mod MOD."""
    res = [[0] * 3 for _ in range(3)]
    for i in range(3):
        Ai = A[i]
        Ri = res[i]
        for k in range(3):
            s = 0
            for j in range(3):
                s += Ai[j] * B[j][k]
            Ri[k] = s % MOD
    return res

def vec_mul(v, A):
    """
    Multiply row vector v (length 3) by 3x3 matrix A: v * A.
    Result is a new vector of length 3, all mod MOD.
    """
    return [
        (v[0] * A[0][0] + v[1] * A[1][0] + v[2] * A[2][0]) % MOD,
        (v[0] * A[0][1] + v[1] * A[1][1] + v[2] * A[2][1]) % MOD,
        (v[0] * A[0][2] + v[1] * A[1][2] + v[2] * A[2][2]) % MOD,
    ]

def build_powers(T, max_bits):
    """Precompute T^(2^k) for k = 0..max_bits-1."""
    powers = [T]
    for _ in range(1, max_bits):
        powers.append(mat_mul(powers[-1], powers[-1]))
    return powers

def apply_steps(dp_vec, steps, powers):
    """
    Apply the base transition 'steps' times:
    dp_vec <- dp_vec * (T^steps),
    using precomputed powers of T.
    """
    bit = 0
    while steps:
        if steps & 1:
            dp_vec = vec_mul(dp_vec, powers[bit])
        steps >>= 1
        bit += 1
    return dp_vec

def main():
    data = sys.stdin.read().strip().split()
    if not data:
        return
    it = iter(data)
    n = int(next(it))
    m = int(next(it))

    blocked = set()   # stores forbidden edges as (u, v) with u < v
    careful = set()   # nodes near forbidden edges that need special handling

    for _ in range(m):
        u = int(next(it))
        v = int(next(it))
        if u > v:
            u, v = v, u
        blocked.add((u, v))
        # Only nodes up to distance 3 from u can be affected by this forbidden edge
        for j in range(u, min(u + 3, n) + 1):
            careful.add(j)

    # Base transition matrix (same as in the C++ solution)
    T = [[0] * 3 for _ in range(3)]
    T[1][0] = 1
    T[2][1] = 1
    T[0][2] = 1
    T[1][2] = 1
    T[2][2] = 1

    # Precompute powers of T up to needed bit length
    max_bits = max(1, n.bit_length() + 1)
    powers = build_powers(T, max_bits)

    # dp is a row vector of length 3; initial vector corresponds to dp[0][2] = 1
    dp = [0, 0, 1]

    careful.add(1)
    careful.add(n)
    points = sorted(careful)

    for i in range(len(points) - 1):
        curr = points[i]
        nxt = points[i + 1]
        if nxt <= curr:
            continue

        if nxt > curr + 1:
            # No forbidden-edge effects in this gap: apply base transition many times
            dp = apply_steps(dp, nxt - curr, powers)
        else:
            # nxt == curr + 1: a single step where forbidden edges around 'nxt'
            # may change the transition matrix
            T2 = [row[:] for row in T]  # copy base transition

            # The following conditions are exactly the ones from the C++ code
            if (nxt - 1, nxt) in blocked:
                T2[2][2] = 0
            if (nxt - 2, nxt) in blocked:
                T2[1][2] = 0
            if ((nxt - 3, nxt - 1) in blocked or
                (nxt - 2, nxt - 1) in blocked or
                (nxt - 2, nxt) in blocked):
                T2[0][2] = 0

            dp = vec_mul(dp, T2)

    # Answer is the same entry as in the original: dp[0][2]
    print(dp[2] % MOD)

if __name__ == "__main__":
    main()

