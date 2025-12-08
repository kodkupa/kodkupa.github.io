/*
@check-accepted: examples small-board medium-board no-limits
*/


// H and W must be coprime and of opposite parity
// The larger side of the board must be at least twice the long movement
// The shorter side of the board must be at least the sum of the short and long movement
// Otherwise the board is too small
// !! It's always possible to complete a 1x1 board

#include <iostream>
#include <numeric>

using namespace std;

long long gcd(long long x, long long y) {
    if (y == 0) return x;

    long long r = x % y;
    while (r) {
        x = y;
        y = r;
        r = x % y;
    }
    return y;
}

int main() {
    int t;
    cin >> t;
    for (; t > 0; t--) {
        long long n, m, h, w;
        bool possible = true;
        cin >> n >> m >> h >> w;
        if (h % 2 == w % 2) {
            possible = false;
        }
        if (gcd(h, w) != 1) {
            possible = false;
        }
        if (max(n, m) < 2 * max(h, w)) {
            possible = false;
        }
        if (min(n, m) < h + w) {
            possible = false;
        }
        if (m == 1 && n == 1) {
            possible = true;
        }

        if (possible) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
        
    }

    return 0;
}
