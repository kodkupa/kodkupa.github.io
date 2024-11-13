#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        long long a, b, k;
        cin >> a >> b >> k;
        
        long long sum = a + b + k;
        long long ans = 0;
        for (long long i = 1; i * i <= sum; i++) {
            if (sum % i == 0) {
                long long dif = 0;
                if (a % i != 0) {
                    dif += i - a % i;
                }
                if (b % i != 0) {
                    dif += i - b % i;
                }
                if (dif <= k) {
                    ans = max(ans, i);
                }
                long long p = sum / i;
                dif = 0;
                if (a % p != 0) {
                    dif += p - a % p;
                }
                if (b % p != 0) {
                    dif += p - b % p;
                }
                if (dif <= k) {
                    ans = max(ans, p);
                }
            }
        }
        
        cout << ans << '\n';
    }
    
    return 0;
}

