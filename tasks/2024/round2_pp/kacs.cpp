// @check-accepted: examples Teljes
// insert brief description of the solution here

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // uncomment the following lines if you want to read/write from files
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    int N, ans = 0, t;

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> t;
        if (1982 <= t)
            ans++;
    }
    cout << ans << "\n";

    return 0;
}
