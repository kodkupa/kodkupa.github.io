// @check-accepted: examples equal max2 no-limits
// insert brief description of the solution here

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {

    int a, b, c;

    cin >> a >> b >> c;
    if (a == b && b == c) {
        cout << "1\n";
    } else if (a == b || b == c || a == c) {
        cout << "3\n";
    } else {
        cout << "6\n";
    }
    return 0;
}
