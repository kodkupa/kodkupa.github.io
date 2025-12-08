#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
const ll M = 998244353LL * 1000000007LL;
int main() {
    int N, S;
    cin >> N >> S;
    vector<ll> V(N);
    vector<ll> knapsack(S + 1);
    for (auto& x : V) cin >> x;
    knapsack[0] = 1;

    auto add = [&](ll x) {
        for (ll i = S; i >= x; --i)
            knapsack[i] = (knapsack[i] + knapsack[i - x]) % M;
    };

    auto remove = [&](ll x) {
        for (ll i = x; i <= S; ++i)
            knapsack[i] = (knapsack[i] + M - knapsack[i - x]) % M;
    };

    for (auto x : V) add(x);
    for (auto x : V) {
        remove(x);
        if (knapsack[S])
            cout << "NO" << endl;
        else
            cout << "YES" << endl;
        add(x);
    }

    return 0;
}
