#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
typedef long long ll;

const int N = 501;
int n, m, t[N], p[N];

ll dp[2][N * N];

struct Job {
    int t, p;
} jobs[N];

void calc_dp() {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j <= min(m, N * N - 1); ++j) {
            dp[0][j] = dp[1][j];

            if (j >= jobs[i].t) {
                dp[0][j] = max(dp[0][j], dp[0][j - jobs[i].t] + jobs[i].p);
            }
        }
        swap(dp[0], dp[1]);
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> jobs[i].t;
    }
    for (int i = 0; i < n; ++i) {
        cin >> jobs[i].p;
    }
    sort(jobs, jobs + n, [](Job x, Job y) {
        return 1ll * x.p * y.t < 1ll * y.p * x.t;
    });
    calc_dp();

    ll ans = 0;
    for (int i = 0; i < min(N * N, m); ++i) {
        int c = (m - i) / jobs[n - 1].t;
        ans = max(ans, 1ll * c * jobs[n - 1].p + dp[1][i]);
    }
    cout << ans << "\n";
}
