// @check-accepted: *

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n, x;
    std::cin >> n >> x;

    std::vector<int> l(n);
    for (int i = 0; i < n; i++) {
        std::cin >> l[i];
    }
    sort(l.begin(), l.end());

    int t = 0;
    for (int i = 0;; ++t) {
        if (i + 1 < n && l[i] + l[i + 1] <= x) {
            i += 2;
        } else if (i < n && l[i] <= x) {
            i += 1;
        } else {
            break;
        }
    }

    std::cout << t << '\n';
}
