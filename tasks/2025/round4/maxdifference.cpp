#include <iostream>
using namespace std;
using ll = long long;

void solve(){
    int N; cin >> N;
    ll ans = 0;
    ll setMin = -1e9;
    ll setMax = -1e9;
    while(N--){
        ll x;
        cin >> x;
        setMax = max(setMax, ans + x);
        setMin = max(setMin, ans - x);
        ans = max(setMax - x, setMin + x);
    }

    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--)solve();
}
