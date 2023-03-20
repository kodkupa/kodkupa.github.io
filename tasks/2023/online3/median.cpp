#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#define all(x) (x).begin(), (x).end()
#define len(x) (int) x.size()
#define lsb(x) (x) & -(x)
#define l(x) (x << 1) + 1
#define r(x) (x << 1) + 2

#define xx first
#define yy second
#define mp make_pair

typedef long long ll;
typedef std::pair <int, int> pii;

const int N = 50003;
int n, pre[N << 1];

ll k;

struct Graph {
    int cnt[N];
    bool stk[N];
    std::vector <pii> adj[N];
} graph;

std::vector <int> weights;

int &get(int i) {
    return pre[i + N];
}

void input()
{
    std::cin >> n >> k;
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        graph.adj[u].push_back({v, w});
        graph.adj[v].push_back({u, w});
        weights.push_back(w);
    }
}

int count(int u) {
    graph.cnt[u] = 1;
    graph.stk[u] = true;
    for (pii p: graph.adj[u]) {
        int v = p.xx;
        if (!graph.stk[v]) {
            graph.cnt[u] += count(v);
        }
    }
    graph.stk[u] = false;
    return graph.cnt[u];
}

int centroid(int u, int c) {
    graph.stk[u] = true;
    int res = 0;
    int mxm = c - graph.cnt[u];
    for (pii p: graph.adj[u]) {
        int v = p.xx;
        if (!graph.stk[v]) {
            mxm = std::max(mxm, graph.cnt[v]);
            res = std::max(res, centroid(v, c));
        }
    }
    if (mxm <= c / 2) {
        res = u;
    }
    graph.stk[u] = false;
    return res;
}

int findCentroid(int u) {
    int c = count(u);
    return centroid(u, c);
}

void calcArr(int u, int q, int &mnm, int &mxm, int &cnt, int omz = 0) {
    graph.stk[u] = true;

    mnm = std::min(mnm, omz);
    mxm = std::max(mxm, omz);
    cnt++;
    get(omz)++;

    for (pii p: graph.adj[u]) {
        int v = p.xx;
        int w = p.yy;
        int d = w <= q? -1: 1;
        if (!graph.stk[v]) {
            calcArr(v, q, mnm, mxm, cnt, omz + d);
        }
    }
    graph.stk[u] = false;
}

ll countAllPairs(int u, int q, int omz = 0) {
    int mnm = 0, mxm = 0, cnt = 0;
    ll res = 0;
    calcArr(u, q, mnm, mxm, cnt, omz);

    for (int i = mnm; i <= mxm; ++i) {
        get(i) += get(i - 1);
    }
    for (int i = mnm; i <= mxm; ++i) {
        int cur = get(i) - get(i - 1);
        int zmo = -i;
        res += 1ll * (zmo >= mnm && zmo <= mxm? get(zmo) : (zmo < mnm? 0: cnt)) * cur;
    }
    for (int i = mnm; i <= mxm; ++i) {
        get(i) = 0;
    }
    return res;
}

ll compute(int u, int q) {
    ll result = countAllPairs(u, q) - 1;
    graph.stk[u] = true;

    for (pii p: graph.adj[u]) {
        int v = p.xx;
        int w = p.yy;
        int d = w <= q? -1: 1;
        if (!graph.stk[v]) {
            result -= countAllPairs(v, q, d);
        }
    }
    return result / 2;
}

ll centroidDecomp(int u, int q) {
    int root = findCentroid(u);
    ll result = compute(root, q);

    graph.stk[root] = true;

    for (pii p: graph.adj[root]) {
        int v = p.xx;
        if (!graph.stk[v]) {
            result += centroidDecomp(v, q);
        }
    }
    return result;
}

ll countAtMost(int q) {
    for (int i = 1; i <= n; ++i) {
        graph.stk[i] = false;
    }
    return centroidDecomp(1, q);
}

int binarySearch(int l, int r) {
    if (l == r) {
        return l;
    }
    int q = l + r >> 1;
    if (countAtMost(weights[q]) < k) {
        return binarySearch(q + 1, r);
    } else {
        return binarySearch(l, q);
    }
}

void solve()
{
    std::sort(all(weights));
    weights.erase(std::unique(all(weights)), weights.end());
    std::cout << weights[binarySearch(0, len(weights) - 1)] << "\n";
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0), std::cout.tie(0);
    input();
    solve();
}

/*
7 15
1 2 3
1 3 1
1 4 4
3 5 1
3 6 5
5 7 9
*/