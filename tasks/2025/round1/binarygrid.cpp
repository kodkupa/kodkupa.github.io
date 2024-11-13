// @check-accepted: examples NMsmall N1 Nsmall no-limits
/**
 *    author:  BERNARD B.01
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt;
  cin >> tt;
  while (tt--) {
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    array<array<int, 2>, 2> dp_cols;
    for (int f1 : {0, 1}) {
      for (int f2 : {0, 1}) {
        dp_cols[f1][f2] = f1 + f2;
      }
    }
    const int inf = int(1e9) + 9;
    for (int i = 2; i < n; i++) {
      array<array<int, 2>, 2> new_dp;
      for (int f1 : {0, 1}) {
        for (int f2 : {0, 1}) {
          new_dp[f1][f2] = inf;
        }
      }
      for (int f1 : {0, 1}) {
        for (int f2 : {0, 1}) {
          for (int f3 : {0, 1}) {
            bool fail = false;
            for (int j = 0; j < m; j++) {
              if ((a[i - 2][j] ^ f1) == (a[i - 1][j] ^ f2) && (a[i - 1][j] ^ f2) == (a[i][j] ^ f3)) {
                fail = true;
                break;
              }
            }
            if (!fail) {
              new_dp[f2][f3] = min(new_dp[f2][f3], f3 + dp_cols[f1][f2]);
            }
          }
        }
      }
      swap(dp_cols, new_dp);
    }
    array<array<int, 2>, 2> dp_rows;
    for (int f1 : {0, 1}) {
      for (int f2 : {0, 1}) {
        dp_rows[f1][f2] = f1 + f2;
      }
    }
    for (int j = 2; j < m; j++) {
      array<array<int, 2>, 2> new_dp;
      for (int f1 : {0, 1}) {
        for (int f2 : {0, 1}) {
          new_dp[f1][f2] = inf;
        }
      }
      for (int f1 : {0, 1}) {
        for (int f2 : {0, 1}) {
          for (int f3 : {0, 1}) {
            bool fail = false;
            for (int i = 0; i < n; i++) {
              if ((a[i][j - 2] ^ f1) == (a[i][j - 1] ^ f2) && (a[i][j - 1] ^ f2) == (a[i][j] ^ f3)) {
                fail = true;
                break;
              }
            }
            if (!fail) {
              new_dp[f2][f3] = min(new_dp[f2][f3], f3 + dp_rows[f1][f2]);
            }
          }
        }
      }
      swap(dp_rows, new_dp);
    }
    int x = inf, y = inf;
    for (int f1 : {0, 1}) {
      for (int f2 : {0, 1}) {
        x = min(x, dp_cols[f1][f2]);
        y = min(y, dp_rows[f1][f2]);
      }
    }
    cout << (x >= inf || y >= inf ? -1 : x + y) << '\n';
  }
  return 0;
}
