// @check-accepted: examples N2 Nsmall no-limits
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;

    vector<int> P(N);
    for (int i = 0; i < N; ++i) cin >> P[i];

    int winner = 0, runnerup = 0;
    winner = max_element(P.begin(), P.begin() + N / 2) - P.begin();
    runnerup = max_element(P.begin() + N / 2, P.end()) - P.begin();
    if (P[winner] < P[runnerup]) swap(winner, runnerup);

    cout << winner << " " << runnerup << endl;

    return 0;
}
