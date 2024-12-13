#!/usr/bin/env python3
# passes with pypy
import sys
input = sys.stdin.readline

MOD = int(1e9 + 7)
NMAX = int(1e6 + 5)
inf = int(1e16)
fact = [1] * (NMAX + 1)


def bin_pow(x, y):
    return pow(x, y, MOD)

def f(n, k):
    sum_ = [0] * (NMAX + 1)
    prefix_prod = [1] * (NMAX + 1)
    suffix_prod = [1] * (NMAX + 1)

    for i in range(1, min(k + 2, n+1)):
        sum_[i] = sum_[i - 1] + bin_pow(i, k)
        if sum_[i] >= MOD:
            sum_[i] -= MOD

    if 0 <= n <= k + 1:
        return sum_[n]

    suffix_prod[k + 2] = 1
    prefix_prod[0] = n
    for i in range(1, k + 2):
        prefix_prod[i] = prefix_prod[i - 1] * (n - i) % MOD
    for i in range(k + 1, -1, -1):
        suffix_prod[i] = suffix_prod[i + 1] * (n - i) % MOD

    ans = 0
    for i in range(k + 2):
        upper = (prefix_prod[i - 1] if i else 0) * suffix_prod[i + 1] % MOD
        lower = fact[i] * fact[k + 1 - i] % MOD
        if (k + 1 - i) % 2:
            lower = (MOD - lower) % MOD
        pi = upper * bin_pow(lower, MOD - 2) % MOD
        ans = (ans + sum_[i] * pi) % MOD
    return ans

def main():
    global MOD, fact
    n, k, MOD = map(int, input().split())
    fact = [1] * (NMAX + 1)
    for i in range(1, NMAX):
        fact[i] = fact[i - 1] * i % MOD

    n %= MOD
    result = ((2 * n + 1) * f(n, k) % MOD - 2 * f(n, k + 1) + 2 * MOD) % MOD
    print(result)
    sys.stdout.close()


if __name__ == "__main__":
    main()
