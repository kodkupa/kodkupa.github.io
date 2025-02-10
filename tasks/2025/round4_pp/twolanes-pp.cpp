// @check-accepted: examples N<=15 lane1=lane2 oneObstacle no-limits
// NOTE: it is recommended to use this even if you don't understand the following code.

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    // uncomment the two following lines if you want to read/write from files
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");

    int N;
    cin >> N;

    string lane1;
    cin >> lane1;

    string lane2;
    cin >> lane2;

    int ans = N;
    for (int i = 0; i < N; i++) {
        if (lane1[i] == 'R' && lane2[i] == 'R') ans = min(ans, i);
    }

    cout << ans << endl;

    return 0;
}
