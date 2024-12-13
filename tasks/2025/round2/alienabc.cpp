// @check-accepted: *
// implementation

#include <iostream>
#include <vector>
using namespace std;

string solv() {
    string S;
    cin >> S;
    vector<bool> one(26, true);
    vector<bool> two(26, true);
    S += '*';
    string res = "";
    int i = 0;
    while (i < S.size() - 1) {
        if (S[i] == S[i + 1]) {
            if (two[S[i] - 'a']) {
                two[S[i] - 'a'] = false;
                res += S[i];
                res += S[i + 1];
                res += ' ';
                i += 2;
            } else {
                return "-1";
            }
        } else {
            if (one[S[i] - 'a']) {
                one[S[i] - 'a'] = false;
                res += S[i];
                res += ' ';
                i += 1;
            } else {
                return "-1";
            }
        }
    }
    return res;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cout << solv() << "\n";
    }
    return 0;
}
