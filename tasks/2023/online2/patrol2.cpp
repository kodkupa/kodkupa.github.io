// @check-accepted: *

#include <iostream>
#include <queue>
#include <vector>

int main() {
    int n, m, l;
    std::cin >> n >> m >> l;

    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    std::vector<int> c(l);
    for (auto &x : c) std::cin >> x;

    std::vector<int> dist(n, 1e8);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> q;
    dist[0] = 0;
    q.push({0, 0});

    while (!q.empty()) {
        auto [d, v] = q.top();
        q.pop();
        if (dist[v] != d) continue;

        for (int u : g[v]) {
            int t = dist[v] + 1;
            if (dist[u] <= t) continue;
            if (c[t % c.size()] != u) {
                dist[u] = t;
                q.push({dist[u], u});
            } else if (t + 1 < dist[u]) {
                dist[u] = t + 1;
                q.push({dist[u], u});
            }
        }
    }

    std::cout << (dist[n - 1] == 1e8 ? -1 : dist[n - 1]) << '\n';
}
