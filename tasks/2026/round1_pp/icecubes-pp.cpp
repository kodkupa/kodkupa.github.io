// @check-accepted: *
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> C(N);
    for (int i = 0; i < N; ++i) {
        cin >> C[i];
    }

    int cubes = 0;
    for (int container : C) {
        if (container > 0) {
            cubes += container - 1;
        }
    }

    cout << cubes << endl;
    return 0;
}
