#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

#define lsb(x) (x) & (-x)
using namespace std;
const int N = 2e5 + 1;
int n, a[N], b[N], p[N], bit[N];

long long ans;

map <int, vector <int>> ind;

int query(int i) {
    int res = 0;
    for (; i; i -= lsb(i)) {
        res += bit[i];
    }
    return res;
}

void update(int i) {
    for (; i < N; i += lsb(i)) {
        bit[i]++;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];

    if (a[1] != b[1] || a[n] != b[n]) {
        cout << "-1\n";
        return 0;
    }
    n--;
    for (int i = 1; i <= n; ++i) {
        a[i] += a[i + 1];
        b[i] += b[i + 1];
    }
    for (int i = 1; i <= n; ++i) {
        if (i & 1) {
            b[i] *= -1;
            a[i] *= -1;
        }
        auto it = ind.find(b[i]);
        if (it == ind.end()) {
            auto p = ind.insert({b[i], {}});
            it = p.first;
        }
        it->second.push_back(i);
    }
    for (int i = n; i >= 1; --i) {
        auto it = ind.find(a[i]);

        if (it == ind.end() || it->second.empty()) {
            cout << "-1\n";
            return 0;
        }
        p[i] = it->second.back();
        it->second.pop_back();
    }
    for (int i = 1; i <= n; ++i) {
        ans += i - 1 - query(p[i]);
        update(p[i]);
    }
    cout << ans << "\n";
}


/*
3 1 4 1 5
4 5 5 6

3 -8 4 1 5
-5 -4 5 6
*/