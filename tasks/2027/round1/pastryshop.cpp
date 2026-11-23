// The changed prices can always be moved inside the range of the unchanged ones, so it is
// optimal to keep N-K consecutive prices in sorted order: O(N log N).

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> P(N);
    for (int i = 0; i < N; i++) {
        cin >> P[i];
    }

    if (K >= N - 1) {
        cout << 0 << endl;
        return 0;
    }

    sort(P.begin(), P.end());
    int keep = N - K;
    int D = P[keep - 1] - P[0];
    for (int i = 1; i + keep <= N; i++) {
        D = min(D, P[i + keep - 1] - P[i]);
    }

    cout << D << endl;
    return 0;
}
