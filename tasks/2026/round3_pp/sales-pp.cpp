// @check-accepted: *
/*  Fast solution in O(N + M) with monotonic stack
 *  
 *  If K[i] > K[j] I don't need j if T[j] < T[i]
 * 
 */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using ll = long long;

int main() {
    int N;
    cin >> N;

    vector<int> W(N);
    for (int i = 0; i < N; ++i)
        cin >> W[i];

    int M;
    cin >> M;

    vector<int> K(M);
    for (int i = 0; i < M; ++i) {
        cin >> K[i];
        K[i] = min(K[i], N);
    }

    vector<int> T(M);
    for (int i = 0; i < M; ++i)
        cin >> T[i];

    vector<int> cnt_sort(N + 1);
    for (int i = 0; i < M; i++) {
        cnt_sort[K[i]] = max(cnt_sort[K[i]], T[i]);
    }

    vector<pair<int, int>> srt;
    for (int i = 1; i <= N; i++) {
        if (cnt_sort[i] == 0) continue;
        while (srt.size() && srt.back().second <= cnt_sort[i]) {
            srt.pop_back();
        }
        srt.push_back({i, cnt_sort[i]});
    }

    int cnt = 0;
    ll sum = 0;
    int ans = 1;

    int j = 0;

    for (int i = 0; i < N; i++) {
        if (sum + (ll)W[i] <= (ll)srt[j].second && cnt < srt[j].first) {
            sum += W[i]; cnt++;
            continue;
        }
        if (
            j == srt.size() - 1 || 
            sum + (ll)W[i] > (ll)srt[j + 1].second
        ) {
            ans++;
            sum = (ll)W[i];
            cnt = 1;
            j = 0;
        } else {
            j++; 
            sum += (ll)W[i]; 
            cnt++;
        }
    }

    cout << ans << '\n';

    return 0;
}
