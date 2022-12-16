#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;

static constexpr ll INF = 1e18;

int main() {
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;

    vector<vector<pair<int, int>>> graph(N);
    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].emplace_back(b, c);
        graph[b].emplace_back(a, c);
    }

    auto dijkstra = [&](int S) {
        priority_queue<pair<ll, int>> Q;
        vector<char> vis(N, false);
        vector<ll> dist(N, INF);
        vector<int> prev(N, -1);

        Q.emplace(0, S);
        dist[S] = 0;

        while (!Q.empty()) {
            int u = Q.top().second;
            Q.pop();
            if (vis[u]) continue;
            vis[u] = true;
            for (auto [v, w] : graph[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    prev[v] = u;
                    Q.emplace(-dist[v], v);
                }
            }
        }

        return make_pair(dist, prev);
    };

    auto [dist1, prev] = dijkstra(0);
    auto [dist2, succ] = dijkstra(N - 1);

    vector<char> visited(N);
    for (int x = 0; x != -1; x = succ[x]) {
        visited[x] = true;
    }

    ll min_dist = dist1[N - 1];
    ll min_diff = INF;

    for (int u = 0; u < N; u++) {
        for (auto [v, w] : graph[u]) {
            if (visited[u] && visited[v]) continue;

            ll diff = ((dist1[u] + w + dist2[v]) - min_dist) + 1;
            if (w - diff > 0) {
                min_diff = min(min_diff, diff);
            }
        }
    }

    if (min_diff == INF) {
        min_diff = -1;
    }
    cout << min_diff << endl;

    return 0;
}
