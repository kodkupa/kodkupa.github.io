// @check-accepted: *
#include <iostream>
#include <string>

int main() {
    std::string a, b;
    std::cin >> a >> b;

    if (a + 'a' == b) {
        std::cout << -1 << '\n';
        return 0;
    }

    std::string c;
    size_t i = 0;
    for (;; ++i) {
        if (a[i] != b[i]) break;
        c += a[i];
    }

    if (i + 1 < b.size()) {
        c += b[i];
        std::cout << c << '\n';
        return 0;
    }

    c += b[i] - 1;
    while (c.back() == a[c.size() - 1]) {
        c += 'z';
    }

    std::cout << c << '\n';
}
