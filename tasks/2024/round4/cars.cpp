// @check-accepted: examples Nsmall no-limits
/**
 *    author:  BERNARD B.01
**/
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

#ifdef B01
#include "deb.h"
#else
#define deb(...)
#endif

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> p(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i];
  }
  int pos = 0;
  while (p[pos] != 1) {
    pos += 1;
  }
  for (int i = 0; i < n; i++) {
    if (p[(pos + i) % n] != i + 1) {
      cout << -1 << '\n';
      return 0;
    }
  }
  cout << (n - pos) % n << '\n';
  return 0;
}
