// @check-accepted: examples two-distinct type1 type2 no-limits
// insert brief description of the solution here

#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int main() {

    int N;
    cin >> N;
    
    vector<int> R(N);
    for (int i = 0; i < N; i++) {
        cin >> R[i];
    }

    int pos = 1;
    vector<int> A, B;
    A.push_back(1);
    B.push_back(1);

    for (int i = 1; i < N; i++) {
        if (R[i - 1] != R[i]) {
            pos++;
            B.push_back(i + 1);
        } else {
            B.push_back(B.back());
        }
        A.push_back(pos);
    }

    assert(A == R || B == R);

    if (A == R) {
        for (int b: B) cout << b << ' ';
    } else {
        for (int a: A) cout << a << ' ';
    }

    cout << endl;

    return 0;
}
