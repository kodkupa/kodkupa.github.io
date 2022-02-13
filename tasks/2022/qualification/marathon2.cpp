/*
1. Minden ellenorzo pont parra (a kiindulasi es vegpontot is beleertve) meg kell mondanunk a legrovidebb utat kozottuk, ezt megtehetjuk a Floyd-Warshall algoritmussal,
ami minden pontpar kozott kiszamitja a legrovidebb utat O(N^3) idoben.
2. Ha adott az ellenorzo pontok egy sorrendje (a kiindulasi es vegpontot is beleertve), a tavolsagszempontjabol csak azon parok szamitanak, amik kozott futva kell kozlekedni
a parok sorrendje irrelevans. Emiatt a sorrend helyett elegendo, ha a parokat hatarozzuk meg, ami az ellenorzo pontok egy maximalis osszegu teljes parositasa (minden pontnak pontosan
egy parja van, es a parokat osszekoto elek osszege maximalis) egy olyan teljes grafban, ami az ellenorzo pontokat tartalmazza es a pontokat osszekoto elek sulya az eredeti grafban
a kozottuk levo legrovidebb ut hossza. Teljes parositas biztosan letezik mert K+2 pont van es K paros. Egy maximalis osszegu teljes parositast a sulyozott Blossom algoritmussal tudunk
keresni O(K^3) idoben (a megvalositasban a Blossom algoritmus mindenkeppen N pontra fut le igy O(N^3) a futasideje).
Komplexitas: O(N^3)
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
constexpr ll INF = 1e18;
constexpr int MAXN = 505;

ll dist[MAXN][MAXN];

struct Blossom {
    struct edge {
        int u, v;
        ll w;
    } g[MAXN * 2][MAXN * 2];
    int n, n_x, match[MAXN * 2], slack[MAXN * 2], st[MAXN * 2], pa[MAXN * 2], flower_from[MAXN * 2][MAXN * 2], S[MAXN * 2], vis[MAXN * 2];
    ll lab[MAXN * 2];
    ll dist(edge const& e) { return lab[e.u] + lab[e.v] - g[e.u][e.v].w * 2; }
    vector<int> flower[MAXN * 2];
    deque<int> q;
    Blossom() {}
    Blossom(int _n) {
        n = _n;
        q = deque<int>();
        for (int u = 1; u <= n * 2; ++u) {
            match[u] = slack[u] = st[u] = pa[u] = S[u] = vis[u] = lab[u] = 0;
            for (int v = 1; v <= n * 2; ++v) {
                g[u][v] = edge{u, v, 0};
                flower_from[u][v] = 0;
            }
            flower[u].clear();
        }
    }
    void add_edge(int u, int v, ll w) {
        ++u;
        ++v;
        g[u][v].w = max(g[u][v].w, w);
        g[v][u].w = max(g[v][u].w, w);
    }
    void update_slack(int u, int x) {
        if (!slack[x] || dist(g[u][x]) < dist(g[slack[x]][x])) slack[x] = u;
    }
    void set_slack(int x) {
        slack[x] = 0;
        for (int u = 1; u <= n; ++u) {
            if (g[u][x].w > 0 && st[u] != x && S[st[u]] == 0) update_slack(u, x);
        }
    }
    void q_push(int x) {
        if (x <= n) return q.push_back(x);
        for (int i = 0; i < (int)flower[x].size(); i++) q_push(flower[x][i]);
    }
    void set_st(int x, int b) {
        st[x] = b;
        if (x <= n) return;
        for (int i = 0; i < (int)flower[x].size(); ++i) set_st(flower[x][i], b);
    }
    int get_pr(int b, int xr) {
        int pr = find(flower[b].begin(), flower[b].end(), xr) - flower[b].begin();
        if (pr % 2 == 1) {
            reverse(flower[b].begin() + 1, flower[b].end());
            return (int)flower[b].size() - pr;
        } else
            return pr;
    }
    void set_match(int u, int v) {
        match[u] = g[u][v].v;
        if (u <= n) return;
        edge e = g[u][v];
        int xr = flower_from[u][e.u], pr = get_pr(u, xr);
        for (int i = 0; i < pr; ++i) set_match(flower[u][i], flower[u][i ^ 1]);
        set_match(xr, v);
        rotate(flower[u].begin(), flower[u].begin() + pr, flower[u].end());
    }
    void augment(int u, int v) {
        int xnv = st[match[u]];
        set_match(u, v);
        if (!xnv) return;
        set_match(xnv, st[pa[xnv]]);
        augment(st[pa[xnv]], xnv);
    }
    int get_lca(int u, int v) {
        static int t = 0;
        for (++t; u || v; swap(u, v)) {
            if (u == 0) continue;
            if (vis[u] == t) return u;
            vis[u] = t;
            u = st[match[u]];
            if (u) u = st[pa[u]];
        }
        return 0;
    }
    void add_blossom(int u, int lca, int v) {
        int b = n + 1;
        while (b <= n_x && st[b]) ++b;
        if (b > n_x) ++n_x;
        lab[b] = 0, S[b] = 0;
        match[b] = match[lca];
        flower[b].clear();
        flower[b].push_back(lca);
        for (int x = u, y; x != lca; x = st[pa[y]]) {
            flower[b].push_back(x), flower[b].push_back(y = st[match[x]]), q_push(y);
        }
        reverse(flower[b].begin() + 1, flower[b].end());
        for (int x = v, y; x != lca; x = st[pa[y]]) {
            flower[b].push_back(x), flower[b].push_back(y = st[match[x]]), q_push(y);
        }
        set_st(b, b);
        for (int x = 1; x <= n_x; ++x) g[b][x].w = g[x][b].w = 0;
        for (int x = 1; x <= n; ++x) flower_from[b][x] = 0;
        for (int i = 0; i < (int)flower[b].size(); ++i) {
            int xs = flower[b][i];
            for (int x = 1; x <= n_x; ++x) {
                if (g[b][x].w == 0 || dist(g[xs][x]) < dist(g[b][x])) g[b][x] = g[xs][x], g[x][b] = g[x][xs];
            }
            for (int x = 1; x <= n; ++x) {
                if (flower_from[xs][x]) flower_from[b][x] = xs;
            }
        }
        set_slack(b);
    }
    void expand_blossom(int b) {  // S[b] == 1
        for (int i = 0; i < (int)flower[b].size(); ++i) set_st(flower[b][i], flower[b][i]);
        int xr = flower_from[b][g[b][pa[b]].u], pr = get_pr(b, xr);
        for (int i = 0; i < pr; i += 2) {
            int xs = flower[b][i], xns = flower[b][i + 1];
            pa[xs] = g[xns][xs].u;
            S[xs] = 1, S[xns] = 0;
            slack[xs] = 0, set_slack(xns);
            q_push(xns);
        }
        S[xr] = 1, pa[xr] = pa[b];
        for (int i = pr + 1; i < (int)flower[b].size(); ++i) {
            int xs = flower[b][i];
            S[xs] = -1, set_slack(xs);
        }
        st[b] = 0;
    }
    bool on_found_edge(const edge& e) {
        int u = st[e.u], v = st[e.v];
        if (S[v] == -1) {
            pa[v] = e.u, S[v] = 1;
            int nu = st[match[v]];
            slack[v] = slack[nu] = 0;
            S[nu] = 0, q_push(nu);
        } else if (S[v] == 0) {
            int lca = get_lca(u, v);
            if (!lca)
                return augment(u, v), augment(v, u), 1;
            else
                add_blossom(u, lca, v);
        }
        return 0;
    }
    bool matching() {
        fill(S, S + n_x + 1, -1), fill(slack, slack + n_x + 1, 0);
        q.clear();
        for (int x = 1; x <= n_x; ++x) {
            if (st[x] == x && !match[x]) pa[x] = 0, S[x] = 0, q_push(x);
        }
        if (q.empty()) return 0;
        for (;;) {
            while ((int)q.size()) {
                int u = q.front();
                q.pop_front();
                if (S[st[u]] == 1) continue;
                for (int v = 1; v <= n; ++v) {
                    if (g[u][v].w > 0 && st[u] != st[v]) {
                        if (dist(g[u][v]) == 0) {
                            if (on_found_edge(g[u][v])) return 1;
                        } else
                            update_slack(u, st[v]);
                    }
                }
            }
            ll d = INF;
            for (int b = n + 1; b <= n_x; ++b) {
                if (st[b] == b && S[b] == 1) d = min(d, lab[b] / 2);
            }
            for (int x = 1; x <= n_x; ++x) {
                if (st[x] == x && slack[x]) {
                    if (S[x] == -1)
                        d = min(d, dist(g[slack[x]][x]));
                    else if (S[x] == 0)
                        d = min(d, dist(g[slack[x]][x]) / 2);
                }
            }
            for (int u = 1; u <= n; ++u) {
                if (S[st[u]] == 0) {
                    if (lab[u] <= d) return 0;
                    lab[u] -= d;
                } else if (S[st[u]] == 1)
                    lab[u] += d;
            }
            for (int b = n + 1; b <= n_x; ++b) {
                if (st[b] == b) {
                    if (S[st[b]] == 0)
                        lab[b] += d * 2;
                    else if (S[st[b]] == 1)
                        lab[b] -= d * 2;
                }
            }
            q.clear();
            for (int x = 1; x <= n_x; ++x) {
                if (st[x] == x && slack[x] && st[slack[x]] != x && dist(g[slack[x]][x]) == 0)
                    if (on_found_edge(g[slack[x]][x])) return 1;
            }
            for (int b = n + 1; b <= n_x; ++b) {
                if (st[b] == b && S[b] == 1 && lab[b] == 0) expand_blossom(b);
            }
        }
        return 0;
    }
    pair<ll, int> solve() {
        fill(match, match + n + 1, 0);
        n_x = n;
        int cnt = 0;
        ll ans = 0;
        for (int u = 0; u <= n; ++u) st[u] = u, flower[u].clear();
        ll w_max = 0;
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                flower_from[u][v] = (u == v ? u : 0);
                w_max = max(w_max, g[u][v].w);
            }
        }
        for (int u = 1; u <= n; ++u) lab[u] = w_max;
        while (matching()) ++cnt;
        for (int u = 1; u <= n; ++u) {
            if (match[u] && match[u] < u) ans += g[u][match[u]].w;
        }
        for (int i = 0; i < n; ++i) match[i] = match[i + 1] - 1;
        return make_pair(ans, cnt);
    }
};

Blossom blossom(500);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N, M, K;
    cin >> N >> M >> K;

    vector<int> C(K);
    for (int i = 0; i < K; i++) {
        cin >> C[i];
    }
    K += 2;
    C.push_back(0);
    C.push_back(N - 1);

    for(int i = 0; i < MAXN; i++)
        for(int j = 0; j < MAXN; j++)
            dist[i][j] = i == j ? 0ll : INF;
    
    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = dist[b][a] = c;
    }

    for(int k = 0; k < N; k++) //Floyd-Warshall
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    for (int i = 0; i < K; i++)
        for (int j = 0; j < K; j++)
            blossom.add_edge(i, j, dist[C[i]][C[j]]);

    auto sol = blossom.solve();
    assert(2 * sol.second == K);

    cout << sol.first << endl;

    return 0;
}