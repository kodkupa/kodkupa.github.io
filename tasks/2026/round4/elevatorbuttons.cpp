// @check-accepted: *
#include <iostream>
#include <string>
using namespace std;

int main() {
    int lo, hi, pos;
    cin >> lo >> hi >> pos;

    string buttons;
    cin >> buttons;

    for (char b : buttons) {
        if (b == 'U') pos += 1;
        else if (b == 'D') pos -= 1;
        else pos = 0; // '0' button

        if (pos < lo || pos > hi) {
            cout << "error\n";
            return 0;
        }
    }

    cout << pos << "\n";
    return 0;
}
