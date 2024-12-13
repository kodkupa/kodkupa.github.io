#include <iostream>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
ll t, n, A[200025], v[200025];

pll add(ll cnt, ll val, ll i, ll x) {
    ll dif = i - cnt;
    dif = min(dif, x);
    cnt += dif;
    x -= dif;
    if (x == 0)
        return {cnt, val};
    ll cat = x / i;
    val += cat;
    x -= cat * i;
    if (x > 0) {
        cnt = x;
        val++;
    }
    return {cnt, val};
}

void solve() {
    cin >> n;
    for (int i = 0; i <= n + 1; i++)
        cin >> A[i];
    n++;
    ll suma = 0;
    for (int i = 1; i <= n; i++) {
        suma += A[i - 1];
        v[i] = suma;
    }
    ll cnt = 1;
    ll val = v[1];
    for (int i = 2; i <= n; i++) {
        if (v[i] < v[i - 1]) {
            ll need = v[i - 1] - v[i];
            if (i == n) {
                cout << "NO\n";
                return;
            }
            cnt++;
            v[i] = v[i - 1];
            v[i + 1] -= need;
            continue;
        }
        ll maxim = 0;
        ll st = 1;
        ll dr = v[i];
        while (st <= dr) {
            ll mij = (st + dr) / 2;
            pll p = add(cnt, val, i - 1, mij);
            if (p.second <= v[i] - mij) {
                maxim = mij;
                st = mij + 1;
            } else
                dr = mij - 1;
        }
        v[i] -= maxim;
        pll p = add(cnt, val, i - 1, maxim);
        cnt = p.first;
        val = p.second;
        if (v[i] == val)
            cnt++;
        else {
            val = v[i];
            cnt = 1;
        }
    }
    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while (t--)
        solve();
    return 0;
}
