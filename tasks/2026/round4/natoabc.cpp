// @check-accepted: *
#include <iostream>
#include <string>

using namespace std;

int main() {
    const string nato[] = {
        "alpha", "bravo", "charlie", "delta", "echo", "foxtrot",
        "golf", "hotel", "india", "juliett", "kilo", "lima",
        "mike", "november", "oscar", "papa", "quebec", "romeo",
        "sierra", "tango", "uniform", "victor", "whiskey", "xray",
        "yankee", "zulu"
    };

    string S;
    cin >> S;

    string decoded;
    int i = 0;
    while (i < S.size()) {
        decoded.push_back(S[i]);
        i += nato[S[i] - 'a'].size();
    }

    cout << decoded << "\n";
    return 0;
}
