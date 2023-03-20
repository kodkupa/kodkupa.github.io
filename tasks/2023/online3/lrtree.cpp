// @check-accepted: examples Nbrute Nsmall no-limits
// n <= 1e6    100p
#include <iostream>
using namespace std;

const int MOD = 1e9 + 7;
int fact[2000001];

int inv(int a) {
    int b = MOD - 2;
    int P = 1;
    while (b) {
        if (b & 1)
            P = (1LL * P * a) % MOD;
        a = (1LL * a * a) % MOD;
        b /= 2;
    }
    return P;
}

int main() {
    int n, i;
    cin >> n;
    fact[0] = fact[1] = 1;
    for (i = 2; i <= 2 * n; i++) 
        fact[i] = (1LL * fact[i - 1] * i) % MOD;
    cout << 1LL * fact[2 * n] * inv(fact[n]) % MOD * inv(fact[n + 1]) % MOD * inv(2) % MOD << endl;
    return 0;
}
