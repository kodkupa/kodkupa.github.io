// @check-accepted: examples C=1 no-limits
// insert brief description of the solution here

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // uncomment the following lines if you want to read/write from files
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    int N, R, C;

    cin >> N >> R >> C;

    if (N > R * C) {
        cout << "NEM" << endl;
    } else {
        cout << "IGEN" << endl;
    }

    return 0;
}
