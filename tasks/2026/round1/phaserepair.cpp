// @check-accepted: examples trivial small few-distinct structured no-limits
#include <ios>
#include <iostream>
#include <istream>
#include <numeric>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    if (!(cin >> N >> M)) return 0;
    vector<int> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];
    if (M == 1) {
        cout << 0 << "\n\n";
        return 0;
    }
    vector<int> occ(M, 0);
    for (int x : a) occ[x] = 1;
    int K = accumulate(occ.begin(), occ.end(), 0);
    if (K <= 1) {
        cout << 0 << "\n\n";
        return 0;
    }
    vector<int> P;
    P.reserve(K);
    for (int r = 0; r < M; r++)
        if (occ[r]) P.push_back(r);
    int best_gap = -1, best_j = 0;
    for (int j = 0; j < K; j++) {
        int cur = P[j], nxt = P[(j + 1) % K];
        int diff = nxt - cur;
        if (diff <= 0) diff += M;  // 1..M-1
        int gap = diff - 1;        // 0..M-2
        if (gap > best_gap) {
            best_gap = gap;
            best_j = j;
        }
    }
    int L = best_gap;
    int B = M - 1 - L;
    int start = P[(best_j + 1) % K];
    cout << B << "\n";
    for (int k = 0; k < B; k++) {
        if (k) cout << ' ';
        int r = start + k;
        if (r >= M) r -= M;
        cout << r;
    }
    cout << "\n";
    return 0;
}
