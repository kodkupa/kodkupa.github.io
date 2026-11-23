#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
using i64 = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    i64 N, M, K, L, U, V; cin >> N >> M >> K >> L >> U >> V;

    vector<i64> X(M), Y(M), Z(M), T(K), P(L);
    for (auto vec: {&X, &Y, &Z, &T, &P})
        for (auto &el: *vec)
            cin >> el;

    sort(T.begin(), T.end());

    vector<vector<tuple<i64, i64, i64>>> adj(N);
    for (int i = 0; i < M; i++) {
        adj[X[i]].emplace_back(Y[i], Z[i], -1);
        adj[Y[i]].emplace_back(X[i], Z[i], -1);
    }

    for (auto &vec: adj)
        sort(vec.begin(), vec.end());

    vector<i64> offsets(L);

    for (int i = 1; i < L; i++) {
        auto &[_, len, pos] = *lower_bound(adj[P[i - 1]].begin(), adj[P[i - 1]].end(), make_tuple(P[i], -1LL, -1LL));
        offsets[i] = offsets[i - 1] + V * len;
        pos = i - 1;
    }

    vector<i64> dst(N, 1e18);
    vector<bool> vis(N);
    priority_queue<pair<i64, i64>, vector<pair<i64, i64>>, greater<>> q;

    q.emplace(dst[0] = 0, 0);

    while (!q.empty()) {
        auto [d, x] = q.top(); q.pop();
        if (vis[x]) continue;
        vis[x] = true;

        for (auto [y, z, tpos]: adj[x]) {
            i64 arrival_time = d + z * U;
            if (tpos != -1) {
                auto it = lower_bound(T.begin(), T.end(), d - offsets[tpos]);
                if (it != T.begin()) {
                    arrival_time = max(arrival_time, *prev(it) + offsets[tpos + 1]);
                }
            }

            if (dst[y] > arrival_time)
                q.emplace(dst[y] = arrival_time, y);
        }
    }

    cout << dst[N - 1] << '\n';
}
