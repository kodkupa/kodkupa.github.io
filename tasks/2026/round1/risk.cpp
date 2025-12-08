// @check-accepted: examples N<=30 N<=300 no-limits

#include <iostream>
#include <string>
#include <algorithm>

void solve() {
    int N, M;
    std::cin >> N >> M;

    int L = (N / 3) + ((N + 1) / 3) + 1;

    if (M > L) {
        std::cout << "filippo" << std::endl;
    } else if (M < L) {
        std::cout << "tommaso" << std::endl;
    } else {
        std::cout << "draw" << std::endl;
    }
}

int main() {
    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
