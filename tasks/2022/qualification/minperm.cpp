// Minperm megoldás

// Vegyük észre hogy a lehetséges cseréket egy gráf éleinek, a pozíciókat pedig
// csúcsainak vehetjük. Ekkor az lesz optimális hogy minden összefüggőségi
// komponensben a növekvő sorrendben vannak számok (belátható hogy bármilyen
// sorrendet előállíthatunk) A komponenst valamilyen bejárással vagy DSU-val
// határozhatjuk meg.

#include <bits/stdc++.h>
using namespace std;

struct dsu {
    vector<int> par;
    vector<int> sz;
    dsu(int n) : par(n, -1) { sz.assign(n, 1); }

    int get(int x) {
        if (par[x] == -1) return x;
        return par[x] = get(par[x]);
    }

    void merge(int x, int y) {
        int px = get(x), py = get(y);
        if (px == py) return;

        if (sz[px] > sz[py]) {
            swap(px, py);
            swap(x, y);  //:) lyft
        }

        sz[py] += sz[px];
        par[px] = py;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector<int> t(n), have(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }

    for (int i = 0; i < k; ++i) {
        int l;
        cin >> l;
        have[l] = 1;
    }

    dsu d(n);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (have[j - i]) {
                d.merge(i, j);
            }
        }
    }

    set<int> s;
    for (int i = 0; i < n; ++i) {
        s.insert(d.get(i));
    }

    vector<int> pos[n];
    vector<int> val[n];

    for (int i = 0; i < n; ++i) {
        pos[d.get(i)].push_back(i);
        val[d.get(i)].push_back(t[i]);
    }

    for (int i = 0; i < n; ++i) {
        sort(pos[i].begin(), pos[i].end());
        sort(val[i].begin(), val[i].end());
    }

    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (int)pos[i].size(); ++j) {
            ans[pos[i][j]] = val[i][j];
        }
    }

    for (auto i : ans) cout << i << " ";
    cout << "\n";
    return 0;
}
