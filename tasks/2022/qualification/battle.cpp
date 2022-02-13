/*
Ha tudjuk a[1], a[2]... a[n] sorrendjet peldaul a[1]>=a[2]...>=a[n], akkor
p[1]>=p[2]...>=p[n] az idealis elrendezes. A konkret ertekek nem is szamitanak,
csak a sorrend. Ha egy kerdeshez kepest, csak ket elemet cserelunk ki (x-et es
y-t), akkkor ki lehet talalni a[x]-a[y]-t. Az elso kerdes utan csak jol ki kell
cserelni ket elemet, es igy midnegyik ertek kitalalhato, osszesen n kerdesben.
*/

#include <bits/stdc++.h>

using namespace std;
const int c = 4005;
long long n, p[c], a[c], alap;
bool v[c], v2[c];

// ha az x es y helyeken levo elemeket csereljuk ki, es a[x] mar ismert, akkor
// ki lehet szamolni a[y]-t is
long long kerd(int x, int y) {
    swap(p[x], p[y]);
    cout << "? ";
    for (int i = 1; i <= n; i++) {
        cout << p[i] << " ";
    }
    cout.flush() << endl;
    swap(p[x], p[y]);
    long long valasz;
    cin >> valasz;
    return valasz;
}

// a[x]-a[1] mar ismert, es ki akarjuk talalni azokat az a[y]-a[1] ertekeket,
// ahol p[x] != p[y]
void dfs(int x) {
    v[x] = true;
    for (int i = 1; i <= n; i++) {
        if (!v[i] && p[x] != p[i]) {
            long long ert = kerd(x, i);
            a[i] = a[x] + (ert - alap) / (p[x] - p[i]);
            dfs(i);
        }
    }
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    alap = kerd(0, 0);
    // csak a kulonbsegek erdekesek, minden ertekbol ki lehet vonni a[1]-et
    dfs(1);

    // rendezes, n^2 idoben (lehet gyorsabban is, de most erre nincs szukseg
    int x = 0;
    for (int i = 1; i <= n; i++) {
        x = 0;
        for (int j = 1; j <= n; j++) {
            if (!v2[j] && (x == 0 || a[j] > a[x])) {
                x = j;
            }
        }
        for (int j = 1; j <= n; j++) {
            if (!v2[j] && p[j] > p[x]) {
                swap(p[j], p[x]);
            }
        }
        v2[x] = 1;
    }

    // a valasz
    cout << "! ";
    for (int i = 1; i <= n; i++) {
        cout << p[i] << " ";
    }
    cout.flush() << endl;
    return 0;
}
