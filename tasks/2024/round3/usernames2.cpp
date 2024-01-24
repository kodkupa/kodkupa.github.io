#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string name;
    cin >> name;
    int n;
    cin >> n;
    unordered_set<string> us;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        us.insert(s);
    }

    string curr = name;
    int ind = 1;
    while (us.count(curr)) {
        curr = name + to_string(ind++);
    }

    cout << curr << "\n";

    return 0;
}
