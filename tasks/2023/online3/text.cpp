// Full score solution
// @check-accepted: *

#include <iostream>
#include <array>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    vector<string> t(n);
    vector<array<int, 26>> cnt(k);
    for (string& s : t) {
        cin >> s;
        for (int i = 0; i < k; i++)
            cnt[i][s[i] -'a']++;
    }

    int mind = n * k;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int d = 0;
        for (int j = 0; j < k; j++) {
            d += n - cnt[j][t[i][j] - 'a'];
        }
        if (d < mind) {
            mind = d;
            ans = i;
        }
    }
    
    cout << ans << endl;
    return 0;
}
