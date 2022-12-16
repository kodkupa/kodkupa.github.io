// greedy_linear solution O(N+K)
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

using namespace std;

constexpr int INF = 1e9;

int N, K;
vector<int> C, T, Q;

int main() {
    cin >> N >> K;
    C.resize(N);
    for (auto &x : C)
		cin >> x;

    T.resize(K);
    Q.resize(K);
    for (int i = 0; i < K; i++)
        cin >> T[i] >> Q[i];

	/* for each bin, calculate the first moment you can empty */
	vector empty_times(N, vector<int>());
	vector bins(N, 0);
	long long ans = 0;

	for (int i = 0; i < K; ++i) {
		auto &idx = T[i];
		auto &qty = Q[i];

		if (bins[idx] == 0 || bins[idx] + qty > C[idx]) {
			/* add index to empty times */
			if (bins[idx] != 0) ans += C[idx] - bins[idx];
			empty_times[idx].push_back(i);
			bins[idx] = qty;
		} else {
			/* substitute the previous index */
			empty_times[idx].back() = i;
			bins[idx] += qty;
		}
	}

	/* add last index */
	for (int i = 0; i < N; ++i) {
		if (empty_times[i].size() > 0) {
			ans += C[i] - bins[i];
		}
	}

	cout << ans << endl;

    return 0;
}
