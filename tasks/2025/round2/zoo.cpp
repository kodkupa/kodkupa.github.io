// @check-accepted: examples cubic quadratic no-limits
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    ll N, M;
    cin >> N >> M;
    vector<vector<int>> g(N);

    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    auto bfs = [&](int src) -> vector<int> {
        queue<int> q;
        vector<int> dist(N, N);
        q.push(src);
        dist[src] = 0;
        while (!q.empty()) {
            int n = q.front();
            q.pop();
            for (auto x : g[n]) {
                if (dist[n] + 1 < dist[x]) {
                    dist[x] = dist[n] + 1;
                    q.push(x);
                }
            }
        }
        return dist;
    };

    auto d_start = bfs(0);
    auto d_end = bfs(N - 1);
    int d = d_start.back();
    vector<int> pref_sum(N + 3, 0);
    for (auto x : d_end) ++pref_sum[x + 2];
    for (int i = 0; i < N + 2; ++i)
        pref_sum[i + 1] += pref_sum[i];

    ll ans = N * (N - 1) / 2 - M;

    for (auto x : d_start) {
        ans -= pref_sum[max(0, d - x)];
    }

    cout << ans << endl;
}
