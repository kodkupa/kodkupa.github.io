// @check-accepted: examples N2 S2 Nsmall distinct no-limits

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];

    int ans = 0;
    int maxi = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] >= maxi) {
            ans++;
            maxi = s[i];
        }
    }
    cout << ans << endl;
    return 0;
}
