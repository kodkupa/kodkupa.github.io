#include <iostream>
using namespace std;

typedef long long ll;
const ll NMAX = 1e6 + 5, NMAX2 = 2.4e7 + 5, inf = 1e16;
ll MOD = 1e9 + 7;

ll binPow(ll x, ll y) {
    ll ans = 1;
    for (; y; y >>= 1, x = x * x % MOD)
        if (y & 1)
            ans = ans * x % MOD;
    return ans;
}

ll sum[NMAX], fact[NMAX], prefixprod[NMAX], suffixprod[NMAX];

ll f(ll n, ll k) {
    for (ll i = 1; i <= k + 1 && i <= n; i++) {
        sum[i] = sum[i - 1] + binPow(i, k);
        if (sum[i] >= MOD)
            sum[i] -= MOD;
    }
    if (0 <= n && n <= k + 1)
        return sum[n];

    suffixprod[k + 2] = 1, prefixprod[0] = n;
    for (ll i = 1; i <= k + 1; i++) prefixprod[i] = prefixprod[i - 1] * (n - i) % MOD;
    for (ll i = k + 1; i >= 0; i--) suffixprod[i] = suffixprod[i + 1] * (n - i) % MOD;

    ll ans = 0;
    for (ll i = 0; i <= k + 1; i++) {
        ll upper = (i ? prefixprod[i - 1] : 1) * suffixprod[i + 1] % MOD;  // upper = [(n-0)*(n-1)*...*(n-(i-1))] * [(n-(i+1))*(n-(i+2))*...*(n-(k+1))]
        ll lower = fact[i] * fact[k + 1 - i] % MOD;
        if ((k + 1 - i) % 2) lower = (MOD - lower) % MOD;  // lower = [(i-0)*(i-1)*...*(i-(i-1))] * [(i-(i+1))*(i-(i+2))*...*(i-(k+1))]
        ll pi = upper * binPow(lower, MOD - 2) % MOD;      // (upper/lower)
        ans += sum[i] * pi % MOD;                          // sum[i]*(upper/lower)
        if (ans >= MOD) ans -= MOD;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll n, k;
    cin >> n >> k >> MOD;
    fact[0] = 1;
    for (ll i = 1; i < NMAX; i++) fact[i] = fact[i - 1] * i % MOD;
    n %= MOD;
    cout << ((2 * n + 1) * f(n, k) % MOD - 2 * f(n, k + 1) + 2 * MOD) % MOD << '\n';
    return 0;
}
