// @check-accepted: examples Rsmall NXRsmall no-limits
// O(NlogN)

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> X(N);
    for (int i = 0; i < N; i++) {
        cin >> X[i];
    }

    vector<int> R(N);
    for (int i = 0; i < N; i++) {
        cin >> R[i];
    }

    vector<pair<int, pair<int, int> > > squares(2 * N);
    for (int i = 0; i < N; i++) {
        squares[2 * i] = make_pair(X[i] - R[i], make_pair(R[i], 1));
        squares[2 * i + 1] = make_pair(X[i] + R[i], make_pair(R[i], -1));
    }

    sort(squares.begin(), squares.end());

    long long res = 0;
    multiset<int> a;
    long long last = 0;
    for (int i = 0; i < 2 * N; i++) {
        if (a.empty()) {
            last = squares[i].first;
            a.insert(squares[i].second.first);
        } else {
            res += (squares[i].first - last) * (*(a.rbegin()));
            if (squares[i].second.second == 1) {
                a.insert(squares[i].second.first);
            } else {
                a.erase(a.find(squares[i].second.first));
            }
            last = squares[i].first;
        }
    }

    cout << 2 * res << endl;  // print the result
    return 0;
}
