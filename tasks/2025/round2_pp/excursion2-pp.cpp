// @check-accepted: examples student-museum students no-limits

#include <fstream>
#include <iostream>
using namespace std;

int main() {
    int A, F, M;
    cin >> A >> F >> M;
    cout << 2 * M + 3 * F + A << '\n';
    cout << M + F + A << '\n';
    return 0;
}
