// NOTE: it is recommended to use this even if you don't understand the
// following code.

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // uncomment the two following lines if you want to read/write from files
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");

    int N, K;
    cin >> N >> K;

    vector<int> C(N);
    for (int i = 0; i < N; ++i) cin >> C[i];

    long long M = 0;
    for (int i = 0; i < min(K,N); ++i) {
        int cur = i;
        int next = (i + 1)%N;
        if (C[cur] > C[next]) swap(C[cur], C[next]);
        M += C[cur];
    }
    if (K >= N) {
        C.erase(max_element(C.begin(), C.end()));
        K -= N;
        --N;
        long long sum = 0;
        for (auto x : C) sum += x;
        for (int i = 0; i < K % N; ++i) M += C[i];
        M += sum * (K / N);
    }

    cout << M << endl;

    return 0;
}
