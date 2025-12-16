#!/usr/bin/env python3

import sys

MOD = 10**9 + 7


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return

    it = iter(data)
    n = next(it)
    # permutation values, 1-based indexing
    t = [0] * (n + 1)
    for i in range(1, n + 1):
        t[i] = next(it)

    fen = [0] * (n + 1)

    def add(idx, delta):
        while idx <= n:
            fen[idx] += delta
            idx += idx & -idx

    def ask(idx):
        s = 0
        while idx > 0:
            s += fen[idx]
            idx -= idx & -idx
        return s

    # First part: count all quadruples (a < b < c < d)
    # with Pa, Pb < Pc < Pd (without caring about Pa vs Pb order);
    # this equals count(1234) + count(2134).
    inc4 = 0
    total = 0

    for i in range(1, n + 1):
        val = t[i]
        before = ask(val)  # how many previous elements < t[i]
        after = n - val - (i - 1) + before  # how many later elements > t[i]
        # choose any two positions before i with value < t[i]
        cnt_pairs = before * (before - 1) // 2
        total = (total + cnt_pairs * after) % MOD
        add(val, 1)

    # reset Fenwick tree
    for i in range(n + 1):
        fen[i] = 0

    # Second part: count increasing subsequences of length 4 (pattern 1234)
    # using DP with Fenwick tree.
    # ert[i] = number of increasing subsequences of current length
    # ending at position i.
    ert = [1] * (n + 1)  # length-1 subsequences

    for length in range(2, 5):  # lengths 2,3,4
        for i in range(1, n + 1):
            val = t[i]
            prev_count = ert[i]
            # number of subsequences of previous length ending at value < t[i]
            cur = ask(val) % MOD
            ert[i] = cur
            add(val, prev_count)

            if length == 4:
                inc4 = (inc4 + cur) % MOD

        # clear Fenwick tree for next length
        for i in range(n + 1):
            fen[i] = 0

    # total = count(1234) + count(2134)
    # inc4  = count(1234)
    ans = (total - inc4) % MOD
    sys.stdout.write(str(ans))


if __name__ == "__main__":
    main()

