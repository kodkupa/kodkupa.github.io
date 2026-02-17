// @check-accepted: examples hardcode naive fixcorner c1dp c2dp full
/**
 *    author:  BERNARD B.01
**/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector a(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }
  vector c(n, vector<int>(m));
  vector<int> cs(n * m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> c[i][j];
      cs[i * m + j] = c[i][j];
    }
  }
  sort(cs.begin(), cs.end());
  cs.resize(unique(cs.begin(), cs.end()) - cs.begin());
  int64_t res = a[0][0];
  const int64_t inf = int64_t(3e18) + 9;
  for (int col : cs) {
    vector dp(n, vector<int64_t>(m, -inf));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (c[i][j] == col) {
          dp[i][j] = a[i][j];
        }
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        dp[i][j] = max(dp[i][j], a[i][j] + max(i > 0 ? dp[i - 1][j] : -inf, j > 0 ? dp[i][j - 1] : -inf));
        if (c[i][j] == col) {
          res = max(res, dp[i][j]);
        }
      }
    }
  }
  cout << res << '\n';
  return 0;
}
