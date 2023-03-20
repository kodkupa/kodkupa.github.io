#include <array>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

constexpr int MAXN = 200;

static int G[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;

    int D = min(N, M);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> G[i][j];
        }
    }

    vector<array<int, MAXN>> dp1(D), dp2(D);

    dp1[0][1] = G[0][1] + G[1][0];
    for (int i = 3; i <= N; i++) {
        int x = min(i, M);
        for (int j = 0; j < x; j++) {
            for (int k = j + 1; k < x; k++) {
                dp2[j][k] = 0;
                if (j > 0) {
                    dp2[j][k] = max(dp2[j][k], dp1[j - 1][k - 1]);
                }
                if (k + 1 < x) {
                    dp2[j][k] = max(dp2[j][k], dp1[j][k]);
                }
                if (j > 0 && k + 1 < x) {
                    dp2[j][k] = max(dp2[j][k], dp1[j - 1][k]);
                }
                if (j != k - 1) {
                    dp2[j][k] = max(dp2[j][k], dp1[j][k - 1]);
                }
                dp2[j][k] += G[i - j - 1][j];
                dp2[j][k] += G[i - k - 1][k];
            }
        }
        swap(dp1, dp2);
    }
    for (int i = M - 1; i >= 2; i--) {
        int x = min(N, i);
        for (int j = 0; j < x; j++) {
            for (int k = j + 1; k < x; k++) {
                dp2[j][k] = dp1[j][k];
                if (k + 1 < N) {
                    dp2[j][k] = max(dp2[j][k], dp1[j][k + 1]);
                    dp2[j][k] = max(dp2[j][k], dp1[j + 1][k + 1]);
                }
                if (j + 1 != k) {
                    dp2[j][k] = max(dp2[j][k], dp1[j + 1][k]);
                }
                dp2[j][k] += G[N - j - 1][M - i + j];
                dp2[j][k] += G[N - k - 1][M - i + k];
            }
        }
        swap(dp1, dp2);
    }

    cout << dp1[0][1] << endl;

    return 0;
}
