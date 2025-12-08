#!/usr/bin/env pypy3
# @check-accepted: *

import sys

class DSURollback:
    class State:
        def __init__(self, a, old_sz, b, old_t, old_bip):
            self.a = a
            self.old_sz = old_sz
            self.b = b
            self.old_t = old_t
            self.old_bip = old_bip

    def __init__(self, n=1):
        self.n = n
        self.bip = 1
        self.t = list(range(2 * n))
        self.sz = [1] * (2 * n)
        self.stk = []

    def is_bipartite(self):
        return self.bip

    def find(self, k):
        if self.t[k] != k:
            return self.find(self.t[k])
        return self.t[k]

    def unite(self, a, b):
        ra = self.find(a)
        rb = self.find(b)
        if self.sz[ra] < self.sz[rb]:
            ra, rb = rb, ra
        self.stk.append(DSURollback.State(ra, self.sz[ra], rb, self.t[rb], self.bip))
        if ra == rb:
            return
        self.sz[ra] += self.sz[rb]
        self.t[rb] = ra

    def add_edge(self, a, b):
        self.unite(a, b + self.n)
        self.bip &= self.find(a) != self.find(a + self.n)
        self.bip &= self.find(b) != self.find(b + self.n)
        self.unite(a + self.n, b)
        self.bip &= self.find(a) != self.find(a + self.n)
        self.bip &= self.find(b) != self.find(b + self.n)

    def undo(self):
        s = self.stk.pop()
        self.sz[s.a] = s.old_sz
        self.t[s.b] = s.old_t
        self.bip = s.old_bip

    def remove_edge(self):
        self.undo()
        self.undo()


class DSUQueue:
    def __init__(self, n):
        self.n = n
        self.ready = 0
        self.updates = []
        self.dsu = DSURollback(n)

    def is_bipartite(self):
        return self.dsu.is_bipartite()

    def find(self, k):
        return self.dsu.find(k)

    def add_edge(self, a, b):
        self.updates.append([a, b, 0])
        self.dsu.add_edge(a, b)

    def remove_edge(self):
        if not self.ready:
            for _ in range(len(self.updates)):
                self.dsu.remove_edge()
            self.updates.reverse()
            for i in range(len(self.updates)):
                a, b, _ = self.updates[i]
                self.updates[i][2] = 1
                self.dsu.add_edge(a, b)
            self.updates.pop()
            self.dsu.remove_edge()
            self.ready = len(self.updates)
        else:
            tmp0 = []
            tmp1 = []
            while self.updates and self.updates[-1][2] == 0:
                tmp0.append(self.updates.pop())
                self.dsu.remove_edge()
            block = self.ready & -self.ready
            for _ in range(block):
                tmp1.append(self.updates.pop())
                self.dsu.remove_edge()
            tmp0.reverse()
            tmp1.reverse()
            for a, b, r in tmp0:
                self.updates.append([a, b, r])
                self.dsu.add_edge(a, b)
            for a, b, r in tmp1:
                self.updates.append([a, b, r])
                self.dsu.add_edge(a, b)
            self.updates.pop()
            self.dsu.remove_edge()
            self.ready -= 1


def read_data():
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    gs = int(next(it))
    edg = int(next(it))
    edges = []
    for _ in range(edg):
        a = int(next(it)) - 1
        b = int(next(it)) - 1
        edges.append((a, b))
    return gs, edg, edges


def solve():
    gs, edg, edges = read_data()
    ret = 0
    dsu = DSUQueue(gs)
    l = 0
    for r in range(edg):
        a, b = edges[r]
        dsu.add_edge(a, b)
        while l < r and not dsu.is_bipartite():
            dsu.remove_edge()
            l += 1
        ret += r - l + 1
    print(ret)


if __name__ == "__main__":
    solve()
