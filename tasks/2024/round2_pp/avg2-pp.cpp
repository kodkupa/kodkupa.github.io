// @check-accepted: examples Ntwo VKsmall Nsmall no-limits
// binary search for the answer

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    long long K;
    cin >> N >> K;
    K *= N;

    long long sum = 0;
    vector<int> v(N);
    for (auto &x : v) {
        cin >> x;
        sum += x;
    }

    if (sum == K) {
        cout << 0 << endl;
        return 0;
    } else if (sum < K) {
        cout << (K - sum + N - 1) / N << endl;
        return 0;
    }

    sort(v.begin(), v.end());
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        long long poss = v[i] - ans - 1;
        if (poss <= 0) continue;
        if (sum - poss * (N - i) > K) {
            sum -= ((long long)(v[i] - ans - 1)) * (N - i);
            ans = v[i] - 1;
        } else {
            ans += (sum - K + N - i - 1) / (N - i);
            break;
        }
    }

    cout << ans << endl;
    return 0;
}
