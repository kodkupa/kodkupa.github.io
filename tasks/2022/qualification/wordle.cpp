// Szozat megoldas

// Ha n hosszu a szo es mar k karakter fix akkor az elso nem fix karakter
// (26-k)-felekeppen valaszthato, a masodik (26-k-1)-felekeppen, majd
// (26-k-2)-felekeppen stb. Tehat a valasz (26-k)*(26-k-1)*...*(26-(n-1)) (mivel
// n-k karaktert kell lefixalnunk es (n-1)-(k)+1=n-k)

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<char> t(n);
    int open = 0;
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
        if (t[i] == '_') open++;
    }

    int closed = n - open;
    int ans = 1;
    for (int i = 0; i < open; ++i) {
        ans *= 26 - closed;
        closed++;
    }

    cout << ans << "\n";
}
