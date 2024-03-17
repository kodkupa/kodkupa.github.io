#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m >> k;
    vector<ll> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i > 0) a[i] += a[i - 1];
    }
    map<ll, ll> lookup;
    for (int i = 0; i < m; i++) {
        cin >> b[i];
        if (i > 0) b[i] += b[i - 1];
        lookup[b[i]] = i;
    }
    vector<ll> pos(n);
    for (int i = 0; i < n; i++) {
        if (lookup.count(a[i])) pos[i] = lookup[a[i]];
        else pos[i] = -1;
    }

    vector<int> lis, ind, prev(n, -1);
    for (int i = 0; i < n; i++) {
        if (pos[i] == -1) continue;
        int j = lower_bound(lis.begin(), lis.end(), pos[i]) - lis.begin();
        if (j == lis.size()) {
            lis.push_back(pos[i]);
            ind.push_back(i);
        } else {
            lis[j] = pos[i];
            ind[j] = i;
        }
        if (j > 0) prev[i] = ind[j - 1];
    }
    
    if (a[n-1] != b[m-1] || lis.size() < k) {
        cout << -1;
        return 0;
    }
    
    vector<int> sa, sb;
    int i = ind.back();
    while (i != -1) {
        sa.push_back(i + 1);
        sb.push_back(pos[i] + 1);
        i = prev[i];
    }
    
    reverse(sa.begin(), sa.end());
    reverse(sb.begin(), sb.end());
    for (int i = 0; i < k - 1; i++) cout << sa[i] << " ";
    cout << "\n";
    for (int i = 0; i < k - 1; i++) cout << sb[i] << " ";
    cout << "\n";

}