#!/usr/bin/env python3
# Full solution with geometric series, O(N + Q log K); the same as minimizeproduct.cpp.
# If [l, r] contains a 0, every sequence of at most k flips is optimal: 1 + T + ... + T^k ways,
# where T is the number of subarrays. Otherwise only the parity of the number of odd-length flips
# matters: among the T^j sequences of j flips, ((E + O)^j +- (E - O)^j) / 2 have an even / odd
# number of odd-length flips (E, O: number of even / odd length subarrays).
import sys

MOD = 998244353
INV2 = (MOD + 1) // 2


def geo(a, k):
    # 1 + a + ... + a^k modulo MOD
    a %= MOD
    if a == 1:
        return (k + 1) % MOD
    return (pow(a, k + 1, MOD) - 1) * pow(a - 1, MOD - 2, MOD) % MOD


def main():
    data = sys.stdin.buffer.read().split()
    n, q = int(data[0]), int(data[1])
    neg = [0] * (n + 1)
    zer = [0] * (n + 1)
    for i in range(n):
        v = int(data[2 + i])
        neg[i + 1] = neg[i] + (v < 0)
        zer[i + 1] = zer[i] + (v == 0)
    out = []
    p = 2 + n
    for _ in range(q):
        l, r, k = int(data[p]), int(data[p + 1]), int(data[p + 2])
        p += 3
        m = r - l + 1
        total = m * (m + 1) // 2  # subarrays
        h = (m + 1) // 2
        odd = h * (m + 1) - h * h  # odd-length subarrays
        all_ways = geo(total, k)
        if zer[r + 1] - zer[l]:
            out.append(all_ways)  # the product is always 0
        elif k == 0:
            out.append(1)
        else:
            sg = geo(total - 2 * odd, k)  # E - O
            if (neg[r + 1] - neg[l]) & 1:
                out.append((all_ways + sg) * INV2 % MOD)  # keep the sign
            else:
                out.append((all_ways - sg) * INV2 % MOD)  # change the sign
    sys.stdout.write("\n".join(map(str, out)) + "\n")


main()
