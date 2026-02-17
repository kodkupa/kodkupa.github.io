// @check-accepted: examples brute cubic line no-limits
#include <climits>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int N, K;
    cin >> N >> K;
    vector<ll> S(N);
    for (auto &x : S)
        cin >> x;
    vector<vector<int>> adj(N);
    for (int i = 1; i < N; ++i) {
        int x;
        cin >> x;
        adj[x].push_back(i);
    }

    vector<vector<ll>> dp(N);
    vector<int> sz(N, 1);

    for (int i = N; i--;) {
        auto &cur = dp[i];
        cur.resize(N + 1, LLONG_MIN);
        cur[0] = 0;
        for (auto x : adj[i]) {
            for (int t = sz[i] + sz[x]; --t;) {
                for (int j = max(t - sz[i], 1); j <= t && j <= sz[x]; ++j) {
                    cur[t] =
                        max(cur[t], cur[t - j] + dp[x][j] + S[i] * j * (t - j));
                }
            }
            sz[i] += sz[x];
        }
        for (int j = sz[i] + 1; --j;) {
            cur[j] = max(cur[j], cur[j - 1] + S[i] * (j - 1));
        }
    }

    cout << dp[0][K] << endl;
}
