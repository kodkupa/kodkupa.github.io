// Full solution: every path costs N*M - 1 (the toll is the increase of i*j), O(1) per query.

#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        long long N, M, K;
        cin >> N >> M >> K;
        cout << (K == N * M - 1 ? "YES" : "NO") << "\n";
    }
    return 0;
}
