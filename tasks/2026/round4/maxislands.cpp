// @check-accepted: *
#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<pair<int, int>> del = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}
};

struct pt {
    int x, y;
    pt() {}
    pt(int _x, int _y) {
        x = _x;
        y = _y;
    }
    vector<pt> adj() {
        vector<pt> res;
        for (auto [dx, dy]: del) {
            if (x + dx >= 0 && x + dx < N &&
                y + dy >= 0 && y + dy < M
            ) {
                res.emplace_back(x + dx, y + dy);
            }
        }
        return res;
    }
};

vector<int> lft;

int max_flow(vector<vector<int>> &adj, int K) {
    int flow = 0;
    vector<int> dst(K), mL(K, -1), mR(K, -1);

    auto dfs = [&](auto &&dfs, int i) -> bool {
        for (int j: adj[i]) {
            int k = mR[j];
            if (k == -1 || (dst[k] == dst[i] + 1 && dfs(dfs, k))) { 
                mL[i] = j;
                mR[j] = i;
                return true;
            }
        }
        dst[i] = -1;
        return false;
    };

    auto bfs = [&]() -> bool {
        queue<int> q;
        bool flag = false;
        for (int i = 0; i < K; i++) {
            if (lft[i] && mL[i] == -1) {
                dst[i] = 0;
                q.push(i);
            } else {
                dst[i] = -1;
            }
        }
        while (!q.empty()) {
            int i = q.front();
            q.pop();
            for (int j: adj[i]) {
                int k = mR[j];
                if (k != -1 && dst[k] == -1) {
                    dst[k] = dst[i] + 1;
                    q.push(k);
                }
                if (k == -1) flag = true;
            }
        }
        return flag;
    };

    while (bfs()) {
        for (int i = 0; i < K; i++) {
            if (lft[i] && mL[i] == -1 && dfs(dfs, i)) {
                flow++;
            }
        }
    }
    return flow;
}

int main() {
    cin >> N >> M;
    vector<string> V(N);
    for (string &v: V) cin >> v;

    int ans = 0;
    vector vis(N, vector<bool>(M));
    vector id(N, vector<int>(M, -1));
    int cnt = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (V[i][j] != '?') continue;
            pt p(i, j);
            for (pt q: p.adj()) {
                if (V[q.x][q.y] == '1') {
                    V[i][j] = '0';
                }
            }
            if (V[i][j] == '?') {
                id[i][j] = cnt++;
            }
        }
    }

    auto explore = [&](auto &&explore, pt p) ->void {
        vis[p.x][p.y] = true;
        for (pt q: p.adj()) {
            if (!vis[q.x][q.y] && 
                V[q.x][q.y] == '1'
            ) {
                explore(explore, q);
            }
        }
    };
    
    lft.assign(cnt, 0);
    vector<vector<int>> ad(cnt);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (vis[i][j] || V[i][j] == '0') 
                continue;
            if (V[i][j] == '1') {
                ans++;
                explore(explore, pt(i, j));
                continue;
            }
            vis[i][j] = true;
            pt p(i, j);
            int idx = id[i][j];
            lft[idx] = (i + j) % 2 == 0;

            for (pt q: p.adj()) {
                if (V[q.x][q.y] == '?') {
                    ad[idx].push_back(id[q.x][q.y]);
                }
            }
        }
    }

    ans += cnt - max_flow(ad, cnt);

    cout << ans << '\n';
}
