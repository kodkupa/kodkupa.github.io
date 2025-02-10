#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main() {
    int n, m;
    cin >> n >> m;
    vector v(n, vector<ll>(m));
    for (auto &vv : v)
        for (auto &x : vv) cin >> x;

    vector<array<ll, 5>> ans;
    auto vert = [&](int x, int y, ll val) {
        ans.push_back({x + 1, y + 1, x + 3, y + 1, val});
        v[x][y] += val;
        v[x + 1][y] += val;
        v[x + 2][y] += val;
    };

    auto hor = [&](int x, int y, ll val) {
        ans.push_back({x + 1, y + 1, x + 1, y + 3, val});
        v[x][y] += val;
        v[x][y + 1] += val;
        v[x][y + 2] += val;
    };

    for (int i = n; i-- > 3;)
        for (int j = 0; j < m; ++j) vert(i - 2, j, -v[i][j]);
    for (int i = 0; i < 3; ++i)
        for (int j = m; j-- > 3;) hor(i, j - 2, -v[i][j]);

    hor(0, 0, -v[0][0]);
    for (int i = 1; i < 3; ++i) {
        ll delta = v[i][0] - v[i - 1][0];
        for (int j = 1; j < 3; ++j)
            if (v[i][j] - v[i - 1][j] != delta) {
                cout << "NO" << endl;
                return 0;
            }
        hor(i, 0, -v[i][0]);
    }

    vert(0, 1, -v[0][1]);
    vert(0, 2, -v[0][2]);

    cout << "YES" << endl;
    sort(ans.begin(), ans.end(), [&](auto a, auto b) { return a[4] > b[4]; });
    cout << ans.size() << endl;
    for (auto x : ans) {
        for (auto y : x) cout << y << ' ';
        cout << endl;
    }
}
