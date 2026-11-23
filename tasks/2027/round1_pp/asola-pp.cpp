#include <iostream>
#include <vector>

using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        int L; cin >> L;
        int K; cin >> K;

        vector<int> X(N);
        for (int &x: X) cin >> x;

        X.insert(X.begin(), -K);
        X.push_back(L);

        string ans = "NO\n";
        for (int i = 1; i < X.size(); i++) {
            if (X[i] - X[i - 1] >= 2 * K) {
                ans = "YES\n";
                break;
            }
        }

        cout << ans;
    }
}
