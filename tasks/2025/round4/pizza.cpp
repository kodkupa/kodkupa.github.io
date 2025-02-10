// @check-accepted: examples MQsmall Nsmall no-limits
// dist[mask] = min(dist[mask ^ i] + a[i] (or b[i] if removing)) over all ingredients i. Time complexity: O(2^N * N + M + Q)
/**
 *    author:  BERNARD B.01
**/
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, q;
  cin >> n >> m >> q;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> b[i];
  }
  vector<int64_t> dist(1 << n, LLONG_MAX / 3);
  for (int i = 0; i < m; i++) {
    int k;
    cin >> k;
    int mask = 0;
    for (int j = 0; j < k; j++) {
      int p;
      cin >> p;
      mask ^= (1 << p);
    }
    dist[mask] = 0;
  }
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < (1 << n); i++) {
      dist[i ^ (1 << j)] = min(dist[i ^ (1 << j)], dist[i] + ((i >> j) & 1 ? b[j] : a[j]));
    }
  }
  while (q--) {
    int k;
    cin >> k;
    int mask = 0;
    for (int j = 0; j < k; j++) {
      int p;
      cin >> p;
      mask ^= (1 << p);
    }
    cout << dist[mask] << '\n';
  }
  return 0;
}
