#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;

const int N = 1e5 + 1;
typedef long long ll;
typedef pair <int, int> pii;
int n, m, k, comp;

struct Graph {
    bool vis[N];
    vector <pii> adj[N];  
} g;

struct Edge {
    int u, v, c;
};

struct Dsu {
    int cnt[N];
    int par[N];

    int root(int u) { 
        return par[u] == u? u: par[u] = root(par[u]);
    }
    void unite(int u, int v) {
        u = root(u), v = root(v);
        if (cnt[u] < cnt[v]) {
            swap(u, v);
        }
        cnt[u] += cnt[v];
        par[v] = u;
    }
};

void dfs(int u) {
    g.vis[u] = true;
    for (auto [v, c]: g.adj[u]) {
        if (!g.vis[v]) {
            dfs(v);
        }
    }
}

pair <ll, ll> opt(int lambda) {
    vector <Edge> edges;
    for (int i = 1; i <= n; ++i) {
        for (auto [v, c]: g.adj[i]) {
            if (i < v) {
                edges.push_back({i, v, c + (i == 1? lambda: 0)});
            }
        }
    }
    Dsu dsu;
    for (int i = 1; i <= n; ++i) {
        dsu.cnt[i] = 1;
        dsu.par[i] = i;
    }
    sort(all(edges), [](Edge x, Edge y) {
        return x.c < y.c || x.c == y.c && x.u < y.u;
    });
    ll cnt = 0, sum = 0;
    for (auto [u, v, c]: edges) {
        if (dsu.root(u) == dsu.root(v)) {
            continue;
        }
        dsu.unite(u, v);
        sum += c;
        if (u == 1) {
            cnt++;
        }
    }
    return {sum, cnt};
}

int binsearch(int l, int r) {
    while (l < r) {
        int q = l + r >> 1;
        if (opt(q).second > k) {
            l = q + 1;
        } else {
            r = q;
        }
    }
    return l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        g.adj[u].push_back({v, c});
        g.adj[v].push_back({u, c});
    }
    g.vis[1] = true;
    for (int i = 2; i <= n; ++i) {
        if (!g.vis[i]) {
            comp++;
            dfs(i);
        }
    }
    if (comp > k) {
        cout << "-1\n";
        return 0;
    }
    int lambda = binsearch(-1e9 + 10, 1e9 + 10);
    if (opt(lambda).second != k) {
        lambda--;
    }
    auto [x, y] = opt(lambda);
    cout << x - 1ll * k * lambda << "\n";
    return 0;
}
