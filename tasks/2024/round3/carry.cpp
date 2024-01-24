// @check-accepted: examples quadratic X=Y no-limits
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#define int long long
using namespace std;
int N;
string A, B;
constexpr int mod = 1e9 + 7;
constexpr int base1 = 2;
constexpr int base2 = 7;
vector<int> p1;
vector<int> p2;
struct Hash {
    vector<int> h1;
    vector<int> h2;
    Hash(const string& s) {
        int n = s.size();
        h1.resize(n + 1);
        h2.resize(n + 1);
        for (int i = 0; i < n; ++i) {
            h1[i + 1] = (h1[i] * base1 + s[i] - '0') % mod;
            h2[i + 1] = (h2[i] * base2 + s[i] - '0') % mod;
        }
    }
    pair<int, int> get(int l, int r) {
        return {(h1[r + 1] - h1[l] * p1[r - l + 1] % mod + mod) % mod, (h2[r + 1] - h2[l] * p2[r - l + 1] % mod + mod) % mod};
    }
};
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    p1.resize(N + 1);
    p1[0] = 1;
    for (int i = 1; i <= N; ++i) {
        p1[i] = p1[i - 1] * base1 % mod;
    }
    p2.resize(N + 1);
    p2[0] = 1;
    for (int i = 1; i <= N; ++i) {
        p2[i] = p2[i - 1] * base2 % mod;
    }
    cin >> A;
    cin >> B;
    for (int i = 0; i < N; ++i) {
        B[i] = 1 - (B[i] - '0') + '0';
    }
    Hash ha(A), hb(B);

    int Q;
    cin >> Q;

    for (int i = 0; i < Q; ++i) {
        int X, Y, L;
        cin >> X >> Y >> L;

        int l = 0, r = L;
        while (l < r) {
            int m = (l + r) / 2;
            if (ha.get(X, X + m) == hb.get(Y, Y + m)) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        if (l == L) {
            cout << 1 << " ";
        } else {
            cout << B[Y + l] << " ";
        }
    }
    cout << '\n';
}
