#!/usr/bin/env python3
# pypy: MLE, python TLE

BLK = 64

def mask(sz):
    """Return a bitmask with the lower sz bits set to 1 (up to BLK bits)."""
    if sz >= BLK:
        return (1 << BLK) - 1
    return (1 << sz) - 1

def popcount(x):
    return x.bit_count()

class Segment:
    def __init__(self, _n):
        # We want self.n (the number of leaves) so that self.n * BLK >= _n.
        self.n = 1
        while self.n * BLK < _n:
            self.n *= 2
        # Allocate segment tree arrays.
        # The tree arrays are 1-indexed, so we need 2*self.n entries.
        self.sum = [0] * (2 * self.n)
        self.lazy = [0] * (2 * self.n)
        # base array for leaves: one 64-bit integer per leaf.
        self.base = [0] * self.n

    def propagate(self, node, seg_len):
        if self.lazy[node]:
            # Clear the lazy flag for this node.
            self.lazy[node] = 0
            # Check if children are internal nodes (non-leaves).
            if node * 2 < self.n:
                left_len = seg_len // 2
                right_len = seg_len // 2
                self.sum[node * 2] = left_len - self.sum[node * 2]
                self.lazy[node * 2] ^= 1
                self.sum[node * 2 + 1] = right_len - self.sum[node * 2 + 1]
                self.lazy[node * 2 + 1] ^= 1
            else:
                # The children are leaves: update their base values.
                # Left child:
                idx = node * 2 - self.n
                self.base[idx] ^= mask(BLK)
                self.sum[node * 2] = popcount(self.base[idx])
                # Right child:
                idx = node * 2 + 1 - self.n
                self.base[idx] ^= mask(BLK)
                self.sum[node * 2 + 1] = popcount(self.base[idx])

    def query(self):
        """Return the total count (stored at the root)."""
        return self.sum[1]

    def _upd(self, node, l, r, ul, ur):
        # No overlap.
        if ul >= r or ur <= l:
            return
        # Leaf node case.
        if node >= self.n:
            # For a leaf node, the segment covers [l, r) where r - l == BLK.
            # We want to toggle bits in the intersection of [ul, ur) with [l, r).
            if ur >= r:
                m1 = mask(BLK)
            else:
                m1 = mask(ur % BLK)
            if ul < l:
                m2 = 0
            else:
                m2 = mask(ul % BLK)
            togglemask = m1 ^ m2
            self.base[node - self.n] ^= togglemask
            self.sum[node] = popcount(self.base[node - self.n])
            return
        # Total overlap.
        if ul <= l and r <= ur:
            self.lazy[node] ^= 1
            self.sum[node] = (r - l) - self.sum[node]
            return
        # Otherwise, propagate lazy flag if necessary.
        self.propagate(node, r - l)
        mid = (l + r) // 2
        self._upd(node * 2, l, mid, ul, ur)
        self._upd(node * 2 + 1, mid, r, ul, ur)
        self.sum[node] = self.sum[node * 2] + self.sum[node * 2 + 1]

    def update(self, l, r):
        """Toggle the bits in the interval [l, r)."""
        self._upd(1, 0, self.n * BLK, l, r)

def main():
    n, m, Q = map(int, input().split())
    ans = 0

    vert = [Segment(n) for _ in range(m + 1)]
    hor = [Segment(m) for _ in range(n + 1)]

    out = []
    for _ in range(Q):
        x1, x2, y1, y2 = map(int, input().split())
        x1 -= 1
        y1 -= 1

        ans -= vert[y1].query()
        ans -= vert[y2].query()
        vert[y1].update(x1, x2)
        vert[y2].update(x1, x2)
        ans += vert[y1].query()
        ans += vert[y2].query()

        ans -= hor[x1].query()
        ans -= hor[x2].query()
        hor[x1].update(y1, y2)
        hor[x2].update(y1, y2)
        ans += hor[x1].query()
        ans += hor[x2].query()

        out.append(str(ans))

    print("\n".join(out))

if __name__ == '__main__':
    main()
