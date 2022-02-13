// Police4 solution

// Dynamic programming solution in which the state is (i, r), the index of the
// current semaphore, and the number of skips used. The DP stores the minimum
// time to reach i having used r skips. Going from i-1 to i takes X[i] - X[i-1]
// time, plus some time spent waiting at i-1 when a skip is not used. The time
// spent at i-1 depends on DP[i-1][r] mod 2*T. To ease the implementation it can
// be beneficial to add 2 phantom semaphores at x=0 and x=L.

// Complexity: O(NR)

#include <bits/stdc++.h>

using namespace std;

const int INF = 1020000000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, r, t, l;
    cin >> n >> r >> t >> l;

    vector<int> v(n);
    for (int &x : v) cin >> x;

    v.insert(v.begin(), 0);
    v.push_back(l);
    n += 2;

    vector<int> dp(r + 1, INF);
    dp[0] = 0;
    for (int i = 1; i < n; i++) {
        vector<int> dp2(r + 1, INF);
        int len = v[i] - v[i - 1];
        for (int j = 0; j <= r; j++) {
            int tmp = dp[j] % (2 * t);
            if (tmp < t) {
                dp2[j] = min(dp2[j], dp[j] + len);
            } else {
                if (j < r) dp2[j + 1] = min(dp2[j + 1], dp[j] + len);
                dp2[j] = min(dp2[j], dp[j] + len + 2 * t - tmp);
            }
        }
        swap(dp, dp2);
    }

    cout << (*min_element(dp.begin(), dp.end())) << '\n';

    return 0;
}
