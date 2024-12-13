// @check-accepted: examples K1 N3 no-limits

#include <fstream>
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

int main() {
    int N, M, K, L;
    cin >> N >> M >> L >> K;
    if (L % 3 && K != 0 || K > (N - L + 1) * (M - L + 1)) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    if (K == 0) {
        for (int i = 0; i < N; ++i)
            cout << string(M, 'R') << endl;
        return 0;
    }
    string col = "RGB";
    vector ans(N, string(M, 'R'));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j) ans[i][j] = col[(i + j) % 3];
    int boundarx = L - 1 + K / (M - L + 1);
    int boundary = L - 1 + K % (M - L + 1);
    char w = col[(boundarx + boundary + 1) % 3];
    if (boundarx < N)
        for (int i = boundary; i < M; ++i) ans[boundarx][i] = w;
    for (int i = boundarx + 1; i < N; ++i)
        for (auto &x : ans[i]) x = w;

    for (auto s : ans) cout << s << endl;

    return 0;
}
