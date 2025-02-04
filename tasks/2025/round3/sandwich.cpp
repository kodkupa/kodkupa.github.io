#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int LIS(vector<i64> &a) {
    vector<i64> lis;
    for (auto x : a) {
        if (x <= 0) continue;
        auto it = lower_bound(lis.begin(), lis.end(), x);
        if (it == lis.end()) {
            lis.push_back(x);
        } else {
            *it = x;
        }
    }
    return lower_bound(lis.begin(), lis.end(), a.back()) - lis.begin() + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;
    vector<i64> A(N, 0);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        assert(A[i] >= -1e9 && A[i] <= 1e9);
        if (i > 0) A[i] += A[i - 1];
    }
    cout << LIS(A) << "\n";
    return 0;
}
