// @check-accepted: *
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

void solve() {
    int N;
    cin >> N;
    vector<int> A(N), B(N), C(N);
    for (int i = 0; i < N; i++) cin >> A[i] >> B[i] >> C[i];

    vector<int> remaining(N);
    iota(remaining.begin(), remaining.end(), 0);

    vector<bool> chosen(N, false);

    // Step 1: sort by apples and bananas
    vector<int> sa = remaining, sb = remaining;
    sort(sa.begin(), sa.end(), [&](int i, int j){ return A[i] < A[j]; });
    sort(sb.begin(), sb.end(), [&](int i, int j){ return B[i] < B[j]; });

    // pick max apple and max banana
    int forcedA = sa.back(); sa.pop_back();
    int forcedB = sb.back(); sb.pop_back();
    chosen[forcedA] = true;
    chosen[forcedB] = true;

    sb.erase(remove(sb.begin(), sb.end(), forcedA), sb.end());
    sa.erase(remove(sa.begin(), sa.end(), forcedB), sa.end());

    // handle odd size
    if (sa.size() % 2 == 1) {
        int leftover = sa.back(); sa.pop_back();
        chosen[leftover] = true;
        sb.erase(remove(sb.begin(), sb.end(), leftover), sb.end());
    }

    // build 2-regular graph
    vector<vector<int>> adj(N);
    for (size_t i = 0; i < sa.size(); i += 2) {
        int u = sa[i], v = sa[i+1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (size_t i = 0; i < sb.size(); i += 2) {
        int u = sb[i], v = sb[i+1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> visited(N, false);
    for (int i = 0; i < N; i++) if (chosen[i]) visited[i] = true;

    for (int start : sa) {
        if (visited[start]) continue;

        vector<int> cycle;
        int cur = start, prev = -1;
        do {
            visited[cur] = true;
            cycle.push_back(cur);
            int nxt = (adj[cur][0] != prev ? adj[cur][0] : adj[cur][1]);
            prev = cur;
            cur = nxt;
        } while (cur != start);

        long long sum_even = 0, sum_odd = 0;
        for (size_t i = 0; i < cycle.size(); i++) {
            if (i % 2 == 0) sum_even += C[cycle[i]];
            else sum_odd += C[cycle[i]];
        }
        if (sum_even >= sum_odd) {
            for (size_t i = 0; i < cycle.size(); i += 2) chosen[cycle[i]] = true;
        } else {
            for (size_t i = 1; i < cycle.size(); i += 2) chosen[cycle[i]] = true;
        }
    }

    // output
    int count = 0;
    for (bool x : chosen) if (x) count++;
    cout << count << "\n";
    for (int i = 0; i < N; i++) if (chosen[i]) cout << i << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
