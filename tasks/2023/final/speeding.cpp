// sorting + two pointers
// @check-accepted: *

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;


int main() {
    // uncomment the following lines if you want to read/write from files
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");

    const ll mod = 1e9 + 7;
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(int& x: a) cin >> x;
    for(int& x: b) cin >> x;
    ll sol = 1;
    ll j = -1;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for(ll i = 0; i < n; i++)
    {
        while(j + 1 < n && b[j + 1] <= a[i]) j++;
        sol = (sol * max(0LL, j + 1 - i)) % mod;
    }
    cout << sol << endl;
    return 0;
}
