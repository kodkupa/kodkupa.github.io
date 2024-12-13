// @check-accepted: examples brute quadratic linear no-limits
// insert brief description of the solution here

#include <iostream>

using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        long long N, K;
        cin >> N >> K;
        long long t = K * (K + 1) / 2;
        if (K == 1 || N == t || N == t + 1)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}
