#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 2;
int t, n, q, r[N];
long long a[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> t;
    while (t--) {
        cin >> n;
        fill(r, r + n + 1, n);

        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n; ++j) {
                if (a[j] % (j - i + 1) != 0) {
                    r[i] = j - 1;
                    break;
                }
            }
        }
        cin >> q;
        for (int i = 0; i < q; ++i) {
            int x, y;
            cin >> x >> y;

            int res = 0;
            for (int j = x; j <= y; ++j) res += min(y, r[j]) - j + 1;
            cout << res << "\n";
        }
    }
}