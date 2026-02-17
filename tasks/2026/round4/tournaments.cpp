// @check-accepted: samples cubic quad lca line bintree full
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;

struct IncreasingChain : map<int, int> {
    void add(int t, int v) {
        auto it = lower_bound(t);
        if (it != end()) {
            if (it->second >= v)
                return;
            if (it->first == t)
                erase(it);
        }
        
        auto [new_elem, _] = emplace(t, v);
        while (new_elem != begin() && prev(new_elem)->second <= v)
            erase(prev(new_elem));
    }

    int query(int t) {
        auto it = lower_bound(t);
        if (it == end()) return 0;
        return it->second;
    }
};

class Centroid {
    vector<vector<int>> adj;
    vector<map<int, int>> dst;
    vector<IncreasingChain> ic;
    vector<int> sz, par, active;

    void find_size(int x, int par = -1) {
        sz[x] = 1;
        for (auto y: adj[x]) {
            if (y != par && active[y]) {
                find_size(y, x);
                sz[x] += sz[y];
            }
        }
    }

    int find_centroid(int x, int tg, int par = -1) {
        for (auto y: adj[x])
            if (y != par && active[y] && 2 * sz[y] >= tg)
                return find_centroid(y, tg, x);
        return x;
    }

    void get_dst(int ctr, int x, int d = 0, int par = -1) {
        dst[ctr][x] = d;
        for (auto y: adj[x])
            if (y != par && active[y])
                get_dst(ctr, y, d + 1, x);
    }

    void decompose(int repr, int parent = -1) {
        find_size(repr);
        int centroid = find_centroid(repr, sz[repr]);

        get_dst(centroid, centroid);

        par[centroid] = parent;
        active[centroid] = false;
        for (auto r: adj[centroid])
            if (active[r])
                decompose(r, centroid);
    }

public:

    void add(int n, int t, int v) {
        for (int ctr = n; ctr != -1; ctr = par[ctr])
            ic[ctr].add(t - dst[ctr][n], v);
    }

    int query(int n, int t) {
        int ans = 0;
        for (int ctr = n; ctr != -1; ctr = par[ctr])
            ans = max(ans, ic[ctr].query(t + dst[ctr][n]));
        return ans;
    }

    Centroid(int N, const vector<int> &A, const vector<int> &B) :
        adj(N), sz(N), par(N), active(N, true), dst(N), ic(N)
    {
        for (int i = 0; i < N - 1; i++) {
            adj[A[i]].push_back(B[i]);
            adj[B[i]].push_back(A[i]);
        }

        decompose(0);
    }
};

int partecipa(int N, int M, vector<int> A, vector<int> B, vector<int> X, vector<int> T) {
    Centroid centroid(N, A, B);

    vector<pair<int, int>> events = {{0, 0}};
    for (int i = 0; i < M; i++)
        events.emplace_back(T[i], X[i]);
    sort(events.begin(), events.end());

    vector<int> dp(M + 1);
    for (int i = M; i >= 0; i--) {
        dp[i] = 1 + centroid.query(events[i].second, events[i].first);
        centroid.add(events[i].second, events[i].first, dp[i]);
    }

    return dp[0] - 1;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, M; cin >> N >> M;
    vector<int> A(N - 1), B(N - 1), X(M), T(M);
    for (int i = 0; i < N - 1; i++)
        cin >> A[i] >> B[i];
    for (int i = 0; i < M; i++)
        cin >> X[i] >> T[i];
    
    cout << partecipa(N, M, std::move(A), std::move(B), std::move(X), std::move(T)) << '\n';
}
