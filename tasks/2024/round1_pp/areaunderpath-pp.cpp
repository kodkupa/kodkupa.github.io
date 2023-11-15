#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7;
const int P = 101;
const int N = 501;

int n, m, p, r, dp[N][N][P];

int calc(int n, int m, int r) {
    if (!m || !n) {
        return !r;
    }
    if (dp[n][m][r] != -1) {
        return dp[n][m][r];
    }
    ll res = 0;
    res += calc(n - 1, m, r);
    res += calc(n, m - 1, (r - n % p + p) % p);
    return dp[n][m][r] = res % mod;
}

int main() {
    cin >> n >> m >> p >> r;
    
    memset(dp, -1, sizeof dp);
    cout << calc(n, m, r) << "\n";
}
