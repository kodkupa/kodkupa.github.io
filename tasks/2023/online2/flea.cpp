// @check-accepted: *

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    int n, ans = 0;
    string s;
    cin >> n >> s;
    for (char c : s) ans += (c == 'L' ? 1 : -1);
    cout << abs(ans) << endl; // print the result
    return 0;
}
