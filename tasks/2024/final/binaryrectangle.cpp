// @check-accepted: examples N<=20 no-limits
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
void solve() {
    int N, M;
    cin >> N >> M;
    vector<string> line(N);
    for (int i = 0; i < N; ++i) cin >> line[i];
    int ans = 0;
    vector<array<int, 3> > ones;
    for (int i = 0; i < N; i++) {
        vector<int> one;
        for (int j = 0; j < M; j++) {
            if (line[i][j] == '1') {
                one.push_back(j);
            }
        }
        for (int j = 1; j < one.size(); j++) {
            if (one[j] != one[j - 1] + 1) {
                cout << 0 << endl;
                return;
            }
        }
        if (one.size() > 0) {
            ones.push_back(array<int, 3>({i, one[0], (int)one.size()}));
        }
    }
    if (ones.size() == 0) {
        cout << 0 << endl;
        return;
    }
    for (int i = 1; i < ones.size(); i++) {
        auto [r, c, l] = ones[i];
        auto [r1, c1, l1] = ones[i - 1];
        if (c1 != c || l1 != l || r != r1 + 1) {
            cout << 0 << endl;
            return;
        }
    }
    cout << 1 << endl;
}
int main() {
    int T;
    cin >> T;
    for (int test = 1; test <= T; ++test) {
        solve();
    }
}
