// @check-accepted: *
// Model solution: sort lengths decreasing and search for
// first two pairs of consecutive equal elements

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // uncomment the following lines if you want to read/write from files
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");

    int n;
    cin >> n;
    
    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    sort(s.rbegin(), s.rend());
    long long a = 0, b = 0;
    for (int i = 1; i < n; i++) {
        if (s[i] == s[i - 1]) {
            if (a == 0) {
                a = s[i];
                i++;
            } else if (b == 0) {
                b = s[i];
                break;
            }
        }
    }

    cout << a * b << endl;
    return 0;
}
