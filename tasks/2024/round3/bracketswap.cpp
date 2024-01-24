// @check-accepted: examples Nsmall Nmedium Nlarge
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    string s;
    cin >> s;
    int bal = 0, mn = 0;
    for (char c : s) {
        bal += c == '(' ? 1 : -1;
        mn = min(mn, bal);
    }
    vector<pair<int, int>> ans;
    int l = 0, r = n - 1;
    while (mn < 0) {
        while (s[l] == '(') l++;
        while (s[r] == ')') r--;
        ans.push_back({l, r});
        swap(s[l], s[r]);
        mn += 2;
    }
    cout << ans.size() << "\n";
    for (auto& [l, r] : ans) {
        cout << l << " " << r << "\n";
    }
}
