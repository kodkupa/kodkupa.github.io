// @check-accepted: examples NQsmall Qsmall Bsmall full
#include <bits/stdc++.h>

using namespace std;

const int max_size = 2e5 + 100, INF = 2e9;

int v[max_size], dist[21][max_size];
vector<int> adj[max_size];

void bfs(int bit, int start) {
    queue<int> q;
    q.push(start);
    dist[bit][start] = 1;
    while (!q.empty()) {
        int nod = q.front();
        q.pop();
        for (auto nei : adj[nod]) {
            if (dist[bit][nei] == INF) {
                dist[bit][nei] = dist[bit][nod] + 1;
                q.push(nei);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        for (int e = 0; e <= 20; e++) {
            if ((v[i] & (1 << e)) != 0) {
                adj[i].push_back(n + e + 1);
                adj[n + e + 1].push_back(i);
            }
        }
    }
    for (int i = 1; i <= n + 21; i++) {
        for (int j = 0; j <= 20; j++) {
            dist[j][i] = INF;
        }
    }
    for (int j = 0; j <= 20; j++) {
        bfs(j, n + j + 1);
    }
    while (q--) {
        int ans = INF, x, y;
        cin >> x >> y;
        for (int j = 0; j <= 20; j++) {
            if (v[x] & (1 << j)) ans = min(ans, dist[j][y]);
        }
        cout << (ans == INF ? -1 : ans / 2) << '\n';
    }
    cout << '\n';
    return 0;
}
