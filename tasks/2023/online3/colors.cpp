// @check-accepted: examples brute Nsmall no-limits
#include <iostream>
#include <map>

using namespace std;

long long mod = 1'000'000'007;

map<long long, int> cnt;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;

    cnt[0] = k;

    long long ans = 1;

    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        ans = (ans * cnt[x]) % mod;
        cnt[x + 1]++;
        cnt[x]--;
    }

    cout << ans << endl;
    return 0;
}
