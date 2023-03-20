// @check-accepted: examples S_12=0 nolimits
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // uncomment the following lines if you want to read/write from files
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");

    int N, P;
    cin >> N >> P;
    
    vector<int> S(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 3; j++) {
            int x;
            cin >> x;
            S[i] += x;
        }
        if (i > 0) {
            S[i] += P * 100;
        }
    }

    int x = *max_element(S.begin() + 1, S.end());
    cout << max(x - S[0] + 1, 0) << endl;

    return 0;
}
