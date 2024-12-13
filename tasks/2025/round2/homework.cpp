// @check-accepted: *
#include <algorithm>
#include <iostream>
using namespace std;

const int c = 550005;
long long n, m, t[c], h[c];  // feladatok szama, ido, feladat hossza, hatarido

long long order1[c], order2[c], inv2[c], spec[c];  // t illetve h szerint rendeze

bool cmp1(int a, int b) {
    return (t[a] < t[b]);
}
bool cmp2(int a, int b) {
    return (h[a] < h[b]);
}

long long fen[c], db[c];
long long lft[c], rght[c], mini[c], sum[c];

int lsb(int a) {
    return (a & -a);
}
void add(int a, int b, long long mul) {
    while (a <= n) {
        fen[a] += b * mul;
        db[a] += mul;
        a += lsb(a);
    }
}
long long ask(long long val) {
    int ans = 0, pos = 0;
    for (int i = 19; i >= 0; i--) {
        int kov = pos + (1 << i);
        if (kov <= n && fen[kov] <= val) {
            val -= fen[kov];
            pos = kov;
            ans += db[kov];
        }
    }
    return ans;
}
void range_add(int a, int l, int r, long long val) {
    if (lft[a] > r || rght[a] < l) {
        return;
    }
    if (l <= lft[a] && rght[a] <= r) {
        sum[a] += val;
        mini[a] += val;
        return;
    }
    int x = 2 * a, y = 2 * a + 1;
    range_add(x, l, r, val), range_add(y, l, r, val);
    mini[a] = sum[a] + min(mini[x], mini[y]);
}
int solve_nlogn() {
    for (int i = 1; i <= n; i++) {
        order1[i] = i, order2[i] = i;
    }
    sort(order1 + 1, order1 + n + 1, cmp1), sort(order2 + 1, order2 + n + 1, cmp2);
    for (int i = 1; i <= n; i++) {
        inv2[order2[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        long long val = t[order1[i]];
        add(i, val, 1);
    }

    int pos = 1;
    int po = 1;
    while (po < n) {
        po *= 2;
    }
    for (int i = po; i < 2 * po; i++) {
        lft[i] = i - po + 1, rght[i] = i - po + 1;
        if (lft[i] <= n) {
            sum[i] = h[order2[lft[i]]];
            mini[i] = sum[i];
        }
    }
    for (int i = po - 1; i >= 1; i--) {
        lft[i] = lft[2 * i], rght[i] = rght[2 * i + 1];
        mini[i] = min(mini[2 * i], mini[2 * i + 1]);
    }

    long long ans = ask(m);
    long long specsum = 0, specdb = 0;
    for (int i = 1; i <= n; i++) {
        int id = order1[i];
        add(i, t[id], -1);
        int hely = inv2[id];
        range_add(1, hely, n, -t[id]);
        specsum += t[id], specdb++;

        if (mini[1] >= 0) {
            ans = max(ans, 2 * specdb + ask(m - specsum));
        } else {
            range_add(1, hely, n, t[id]);
            specsum -= t[id], specdb--;
            add(i, t[id], 1);
        }
    }

    for (int i = 0; i < 2 * po; i++) {
        lft[i] = 0, rght[i] = 0, sum[i] = 0, mini[i] = 0;
    }
    for (int i = 0; i <= n; i++) {
        fen[i] = 0, db[i] = 0;
        order1[i] = 0, order2[i] = 0, inv2[i] = 0;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    for (int w = 1; w <= tc; w++) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            cin >> t[i] >> h[i];
        }

        cout << solve_nlogn() << "\n";
    }
}
