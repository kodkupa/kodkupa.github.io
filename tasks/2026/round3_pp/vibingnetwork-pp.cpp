// @check-accepted: examples small_T k_equals_1 full
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N;
    int T, K;
    cin >> N >> T >> K;

    // Compute need = ceil(67*N/100) = (67*N + 99)/100
    long long need = (67LL * N + 99) / 100;

    int streak = 0;
    for (int i = 1; i <= T; i++) {
        long long a;
        cin >> a;
        
        if (a >= need) {
            streak++;
        } else {
            streak = 0;
        }

        if (streak == K) {
            cout << (i - K + 1) << "\n";
            return 0;
        }
    }
    
    cout << -1 << "\n";
    return 0;
}
