// linear, greedy
// @check-accepted: *

#include <array>
#include <iostream>
#include <vector>

using namespace std;

int mod3(const string& s) {
    int sum = 0;
    for (char c : s) sum += c - '0';
    return sum % 3;
}

string without_leading_0(const string& s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != '0') return s.substr(i);
    }
    return "";
}

// biggest result if cnt digits of rem remainder are deleted
string remove(string s, int cnt, int rem) {
    // remove first where the next is bigger
    for (int i = 0; i + 1 < s.size(); i++) {
        if ((s[i] - '0') % 3 == rem && s[i + 1] > s[i]) {
            s.erase(i, 1);
            i = max(-1, i - 2);
            cnt--;
            if (cnt == 0) return s;
        }
    }
    // remove last (next will be smaller or equal for sure)
    for (int i = s.size() - 1; i >= 0; i--) {
        if ((s[i] - '0') % 3 == rem) {
            s.erase(i, 1);
            cnt--;
            if (cnt == 0) return s;
        }
    }
    return "";
}

void solve() {
    string s;
    cin >> s;
    int rem = mod3(s);
    if (rem == 0) {
        cout << s << "\n";
        return;
    }
    string one = without_leading_0(remove(s, 1, rem));
    string two = without_leading_0(remove(s, 2, 3 - rem));
    if (one.size() > two.size() || one.size() == two.size() && one > two) {
        cout << one << "\n";
    } else {
        if (two != "") cout << two << "\n";
        else cout << "-1\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        solve();
    }

    return 0;
}
