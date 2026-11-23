#!/usr/bin/env python3
# Keep N-K consecutive prices in sorted order: O(N log N).


# input data
N, K = map(int, input().strip().split())
P = list(map(int, input().strip().split()))

if K >= N - 1:
    print(0)
else:
    P.sort()
    keep = N - K
    print(min(P[i + keep - 1] - P[i] for i in range(N - keep + 1)))
