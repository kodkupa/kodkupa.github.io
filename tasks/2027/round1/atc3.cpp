#include <algorithm>
#include <iostream>
#include <array>
#include <queue>
#include <vector>
#include <set>
#include <cassert>
#include <string>

#define all(X) begin(X), end(X)
#define mp make_pair

using namespace std;
using ll = long long;

class TwoSatSolver {
    int N_clauses;
    vector<vector<int>> adj, rev;
    vector<bool> value;

    bool _solve() {
        vector<int> comp(2 * N_clauses + 2);
        vector<bool> vis(2 * N_clauses + 2);
        vector<int> order;

        auto dfs = [&](auto &&dfs, int i) -> void {
            vis[i] = true;
            for (int j: adj[i]) {
                if (!vis[j]) dfs(dfs, j);
            }
            order.push_back(i);
        };

        for (int i = 2; i <= 2 * N_clauses + 1; i++) {
            if (!vis[i]) dfs(dfs, i);
        }

        int cmp = 1;

        auto find_comp = [&](auto &&self, int i) -> void {
            for (int j: rev[i]) {
                if (!comp[j]) {
                    comp[j] = comp[i];
                    self(self, j);
                }
            }
        };

        reverse(all(order));
        for (int i: order) {
            if (!comp[i]) {
                comp[i] = cmp++;
                find_comp(find_comp, i);
            }
        }

        vector<vector<int>> adj_comp(cmp);
        vector<int> indeg(cmp);

        for (int i = 1; i <= N_clauses; i++) {
            if (comp[2 * i] == comp[2 * i + 1])
                return false;

            for (int j: adj[2 * i]) {
                if (comp[j] == comp[2 * i]) continue;
                adj_comp[comp[2 * i]].push_back(comp[j]);
                indeg[comp[j]]++;
            }
            for (int j: adj[2 * i + 1]) {
                if (comp[j] == comp[2 * i + 1]) continue;
                adj_comp[comp[2 * i + 1]].push_back(comp[j]);
                indeg[comp[j]]++;
            }
        }

        queue<int> q;
        vector<int> toposort, time(cmp);


        for (int i = 1; i < cmp; i++) {
            if (indeg[i] == 0)
                q.push(i);
        }

        while (!q.empty()) {
            int i = q.front();
            q.pop();
            toposort.push_back(i);
            time[i] = toposort.size();
            for (int j: adj_comp[i]) {
                if (--indeg[j] == 0) {
                    q.push(j);
                }
            }
        }

        for (int i = 1; i <= N_clauses; i++) {
            value[i] = time[comp[2 * i + 1]] < time[comp[2 * i]];
        }
        return true;
    }

public:
    TwoSatSolver(int N) : N_clauses(N) {
        adj.resize(2 * N + 2);
        rev.resize(2 * N + 2);
        value.resize(N + 1);
    }
    void add_clause(int a, int b) {

        if (!a || abs(a) > N_clauses) return;
        if (!b || abs(b) > N_clauses) return;

        int _a = (abs(a) << 1) ^ (a < 0);
        int _b = (abs(b) << 1) ^ (b < 0);

        adj[_a ^ 1].push_back(_b);
        adj[_b ^ 1].push_back(_a);

        rev[_b].push_back(_a ^ 1);
        rev[_a].push_back(_b ^ 1);
    }

    vector<bool> solve() {
        return _solve() ? value : vector<bool>();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    ll K;
    cin >> N >> M >> K;

    vector<array<ll, 4>> F(M + 1);

    vector<vector<pair<ll, int>>> T(N);

    for (int i = 1; i <= M; i++) {
        auto &[a, t1, b, t2] = F[i];
        cin >> a >> t1 >> b >> t2;
        T[a].emplace_back(t1, i);
        T[b].emplace_back(t2, i);
    }

    int clause_id = M + 1;

    vector<pair<int, int>> clauses;

    for (int i = 0; i < N; i++) {
        sort(all(T[i]));
        vector<int> id(4 * T[i].size());

        auto rec = [&](auto &&rec, int ti, int sl, int sr) -> void {
            if (sr - sl < 1) return;
            id[ti] = clause_id++;
            for (int j = sl; j < sr; j++) {
                clauses.emplace_back(-id[ti], -T[i][j].second);
            }
            if (sr - sl == 1) return;
            int mid = sl + sr >> 1;
            rec(rec, 2 * ti, sl, mid);
            rec(rec, 2 * ti + 1, mid, sr);
        };

        rec(rec, 1, 0, T[i].size());

        auto add_range = [&](
            auto &&self, int ti, int sl, int sr, int l, int r, int n_i
        ) -> void {
            if (sl >= r || sr <= l) return;
            if (sl >= l && sr <= r) {
                clauses.emplace_back(-n_i, id[ti]);
                return;
            }
            int mid = sl + sr >> 1;
            self(self, 2 * ti, sl, mid, l, r, n_i);
            self(self, 2 * ti + 1, mid, sr, l, r, n_i);
        };

        int l = 0, r = 0;
        for (int j = 0; j < T[i].size(); j++) {
            while (l < j && T[i][l].first < T[i][j].first - K) l++;
            while (r < T[i].size() && T[i][r].first <= T[i][j].first + K) r++;

            if (l < j)
                add_range(add_range, 1, 0, T[i].size(), l, j, T[i][j].second);
            if (r > j + 1)
                add_range(add_range, 1, 0, T[i].size(), j + 1, r, T[i][j].second);
        }
    }

    TwoSatSolver sat(clause_id);

    for (auto [a, b]: clauses) {
        sat.add_clause(a, b);
    }

    int L; cin >> L;
    for (int i = 0; i < L; i++) {
        int u, v;
        cin >> u >> v;
        sat.add_clause(u + 1, v + 1);
    }

    auto ans = sat.solve();

    if (ans.size() == 0) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";

    for (int i = 1; i <= M; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}
