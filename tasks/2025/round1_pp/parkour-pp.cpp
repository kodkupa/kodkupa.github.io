// @check-accepted: *
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    if (N > M) {
        cout << "-1\n";
        return 0;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (j < i)
                cout << "#";
            else
                cout << ".";
        }
        cout << endl;
    }
}
