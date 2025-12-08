// @check-accepted: examples NoUpFirstBoost NoUp NoHor AtMostTwoHor no-limits
// insert brief description of the solution here

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int sol() {
    int N;
    string S;
    cin >> N >> S;

    int speed = 0;
    int horizontal = 0;
    int ans = 0;

    for (char c : S) {
        if (c == 'D')
            speed += 9;
        else if (c == 'U')
            speed -= 11;
        else if (c == 'B')
            speed += 10;
        else
            horizontal += 1;

        if (speed <= 0) {
            int need = (10 - speed) / 10;
            if (need > horizontal)
                return -1;
            ans = max(ans, need);
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << sol() << "\n";
    return 0;
}
