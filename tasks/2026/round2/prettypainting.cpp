#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int N;
    cin >> N;
    vector<ll> K(N), P(N - 1), W(N - 1);
    for (auto& x : K) cin >> x;
    for (auto& x : P) cin >> x;
    for (auto& x : W) cin >> x;
    P.insert(P.begin(), 0);
    W.insert(W.begin(), 0);

    vector<vector<int>> adj(N);
    for (int i = 1; i < N; ++i) adj[P[i]].push_back(i);

    vector<ll> dp(N, 0), dp_free(N, 0);

    for (int i = N; i--;) {
        ll cur_ans = 0;
        vector<ll> gains;
        gains.reserve(adj[i].size());
        for (auto x : adj[i]) {
            cur_ans += dp[x];
            if (K[x])
                gains.push_back(max(0LL, dp_free[x] + W[x] - dp[x]));
            else
                gains.push_back(0);
        }
        sort(gains.rbegin(), gains.rend());
        for (int j = 0; j < K[i] - 1; ++j) cur_ans += gains[j];
        dp_free[i] = cur_ans;
        if (K[i] > 0 && K[i] <= gains.size()) cur_ans += gains[K[i] - 1];
        dp[i] = cur_ans;
    }
    cout << dp[0] << endl;
}
