// @check-accepted: examples cubic quadratic all
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
vector<int> v[200005];
vector<int> ans(200005);
multiset<int> q[200005];
int sum[200005];
int ma[200005];
int dfs(int pos, int prec) {
    int m = 0;
    int tot = 0;
    for (int x : v[pos]) {
        if (x == prec) continue;
        int k = dfs(x, pos);
        tot += k;
        m = max(m, k);
        q[pos].insert(k);
    }
    sum[pos] = tot + 1;
    ma[pos] = m;
    q[pos].insert(0);
    q[pos].insert(0);
    return tot - m + 1;
}
void reroot(int pos, int prec) {
    ans[pos] = sum[pos] - ma[pos];

    for (int x : v[pos]) {
        if (x == prec) continue;
        sum[pos] -= (sum[x] - ma[x]);
        q[pos].erase(q[pos].find(sum[x] - ma[x]));
        ma[pos] = *prev(q[pos].end());
        sum[x] += sum[pos] - ma[pos];
        q[x].insert(sum[pos] - ma[pos]);
        ma[x] = *prev(q[x].end());

        reroot(x, pos);

        sum[x] -= sum[pos] - ma[pos];
        q[x].erase(q[x].find(sum[pos] - ma[pos]));
        ma[x] = *prev(q[x].end());
        sum[pos] += (sum[x] - ma[x]);
        q[pos].insert(sum[x] - ma[x]);
        ma[pos] = *prev(q[pos].end());
    }
}

int main() {
    ios::sync_with_stdio(false);
    int N;
    cin >> N;
    for (int i = 0, a, b; i < N - 1; i++) {
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    dfs(0, -1);
    reroot(0, -1);
    for (int i = 0; i < N; i++) cout << ans[i] << " ";
    cout << '\n';
}
