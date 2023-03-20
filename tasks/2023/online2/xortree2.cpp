#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <set>
#include <map>

#define l(x) (x << 1) + 1
#define r(x) (x << 1) + 2
typedef std::pair<int, int> pii;
const int N = 1e5 + 1;
const int L = 30;
int n, q, answers[N];

struct Graph {
    int value[N];
    std::vector <pii> adj[N];

    void add_edge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
} graph;

struct Node {
    int l, r;
    std::vector <int> updates;
} node[N << 2];

struct Trie {
    static int nextIndex;

    int nxt[N * L][2];
    int cnt[N * L];

    void change(int key, int val) {
        int curr = 0;
        for (int i = L - 1; i >= 0; --i) {
            int b = key >> i & 1;
            if (nxt[curr][b]) {
                curr = nxt[curr][b];
            } else {
                curr = nxt[curr][b] = nextIndex++;
            }
            cnt[curr] += val;
        }
    }

    int maxXor(int key) {
        int curr = 0, result = 0;
        for (int i = L - 1; i >= 0; --i) {
            int b = key >> i & 1;
            int c = nxt[curr][!b];
            if (c && cnt[c]) {
                result ^= 1 << i;
            } else {
                c = nxt[curr][b];
            }
            curr = c;
        }
        return result;
    }
} trie;

int Trie::nextIndex = 1;

void dfs(int u, int par = 0, int value = 0) {
    graph.value[u] = value;
    for (pii p: graph.adj[u]) {
        int v = p.first;
        int w = p.second;
        if (par != v) {
            dfs(v, u, value ^ w);
        }
    }
}

void build(int id, int l, int r) {
    node[id].l = l;
    node[id].r = r;
    if (l == r) {
        return;
    }
    int q = l + r >> 1;
    build(l(id), l, q);
    build(r(id), q + 1, r);
}

void update(int id, int l, int r, int value) {
    if (node[id].l == l && node[id].r == r) {
        node[id].updates.push_back(value);
        return;
    }
    int q = node[id].l + node[id].r >> 1;
    if (l <= q) {
        update(l(id), l, std::min(q, r), value);
    }
    if (r > q) {
        update(r(id), std::max(q + 1, l), r, value);
    }
}

std::set <int> inside;

void traverse(int id, int answer = 0) {
    for (int key: node[id].updates) {
        trie.change(key, 1);
        inside.insert(key);
        answer = std::max(answer, trie.maxXor(key));
    }
    if (node[id].l == node[id].r) {
        answers[node[id].l] = answer;
    } else {
        traverse(l(id), answer);
        traverse(r(id), answer);
    }
    for (int key: node[id].updates) {
        inside.erase(key);
        trie.change(key, -1);
    }
}

int main() {
    std::cin >> n >> q;
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        graph.add_edge(u, v, w);
    }
    dfs(1);
    build(0, 0, q);
    std::map<int, int> vertices;
    for (int i = 1; i <= n; ++i) {
        // vertices[i] = 0;
    }
    for (int i = 1; i <= q; ++i) {
        int u;
        std::cin >> u;
        if (vertices.count(u)) {
            update(0, vertices[u], i - 1, graph.value[u]);
            vertices.erase(u);
        } else {
            vertices[u] = i;
        }
    }
    for (auto vert: vertices) {
        update(0, vert.second, q, graph.value[vert.first]);
    }
    traverse(0, 0);
    for (int i = 1; i <= q; ++i) {
        std::cout << answers[i] << "\n";
    }
}

/*
5 7
1 2 1
1 3 2
3 4 4
4 5 3
1
2
3
2
4
5
4

{1}
{1, 2}
{1, 2, 3}
{1, 3}
{1, 3, 4}
{1, 3, 4, 5}
{1, 3, 5}
*/