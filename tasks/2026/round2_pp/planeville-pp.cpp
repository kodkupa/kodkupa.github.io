// @check-accepted: examples Visone Nsmall Vsmall no-limits
// insert brief description of the solution here

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
    
    vector<int> V(N);
    for (int i = 0; i < N; i++) {
        cin >> V[i];
    }

    int ans = 0;
    for(int i = 0; i < N; i++){
        ans += 2;
        ans += V[i];
    }
    cout << ans << "\n";
    return 0;
}
