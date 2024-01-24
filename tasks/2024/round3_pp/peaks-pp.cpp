// @check-accepted: examples N1 NMsmall no-limits
// insert brief description of the solution here

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {

    int N, M;
    cin >> N >> M;
    vector<int> A(N), B(M);
    for(int &x: A) cin >> x;
    for(int &x: B) cin >> x;

    long long peaksA = 0, peaksB = 0;

    for(int i = 0; i < N; ++i)
        if((i == 0 || A[i] > A[i-1]) && (i == N-1 || A[i] > A[i+1]))
            ++peaksA;
    for(int i = 0; i < M; ++i)
        if((i == 0 || B[i] > B[i-1]) && (i == M-1 || B[i] > B[i+1]))
            ++peaksB;

    cout << peaksA * peaksB << endl;

    return 0;
}
