// @check-accepted: examples K1 NKsmall NKmedium no-limits
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

const int N_MAX = 200000;

int T, N, K, M;
set <int> G[N_MAX + 5];
int tricks[N_MAX + 5];
bool known[N_MAX + 5];
int dp[N_MAX + 5];

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    for(int i = 1; i <= N; i++) {
        cin >> tricks[i];
    }

    int mx = 0;
    for(cin >> M; M; M--) {
        int x, y;
        cin >> x >> y;
        G[x].insert(y);
        mx = max(mx, (int)G[x].size());
    }
    // cerr << mx << "\n";
    dp[1] = tricks[1] <= K;
    dp[2] = tricks[2] <= K;

    if(G[tricks[1]].count(tricks[2]) && tricks[2] <= K) {
        dp[2] = 1 + dp[1];
    }

    for(int i = 3; i <= N; i++) {
        if(tricks[i] > K) {
            continue;
        }
        int t = -1;
        for(int j = 1; j <= 2; j++) {
            if(G[tricks[i - j]].count(tricks[i]) && tricks[i - j] <= K) {
                if(t == -1) {
                    t = i - j;
                }
                else if(dp[i - j] > dp[t]) {
                    t = i - j;
                }
            }
        }
        if(t == -1 || dp[t] == 0) {
            continue;
        }
        dp[i] = 1 + dp[t];
    }

    cout << max(dp[N], dp[N - 1]) << "\n";
    return 0;
}
