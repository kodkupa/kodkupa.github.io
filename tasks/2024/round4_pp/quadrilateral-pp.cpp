// @check-accepted: examples Nsmall Nmid no-limits
// O(Nlog(N)). a <= b <= c <= d for a quadrilateral iff a+b+c>d ...

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // uncomment the following lines if you want to read/write from files
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");

    int N;
    cin >> N;
    
    vector<long long> S(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }

    sort(S.begin(), S.end());
    for (int i = 0; i < N-3; i++) {
        if (S[i]+S[i+1]+S[i+2] > S[i+3]) {
	    //cout << "POSSIBLE" << endl;
	    cout << S[i] << " " << S[i+1] << " " <<  S[i+2] << " " << S[i+3] << endl;
	    return 0;
        }
    }

    //cout << "IMPOSSIBLE" << endl;
    cout << "-1" << endl;
    return 0;
}
