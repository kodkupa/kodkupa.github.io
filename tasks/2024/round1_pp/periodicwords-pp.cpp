#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

const int kN = 1e5;
vector<int> divs[1 + kN];

void precalc(int n) {
  for (int i = 1; i <= n; ++i) {
    for (int j = 2 * i; j <= n; j += i) {
      divs[j].emplace_back(i);
    }
  }
} 

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  string s;
  cin >> n >> s;
  
  s = '$' + s;

  precalc(n);

  int q;
  cin >> q;

  for (int qq = 0; qq < q; ++qq) {
    int l, r;
    cin >> l >> r;
    l++, r++;

    bool ok = false;

    for (const int len : divs[r - l + 1]) {
      ok = true;

      for (int i = l; i < l + len && ok; ++i) {
        for (int j = i + len; j <= r && ok; j += len) {
          if (s[i] != s[j]) {
            ok = false;
          }
        }
      }

      if (ok) {
        break;
      }
    }

    if (ok) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }

  return 0;
}