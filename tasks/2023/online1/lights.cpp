#include <iostream>
#include <vector>

int main() {
    int n, c;
    std::cin >> n >> c;

    std::vector<int> l(n);
    for (auto &x : l) std::cin >> x;

    int ans = n;
    int zeros = c;
    std::vector<int> f(c);
    for (int j = 0, i = 0; j < n;) {
        if (f[l[j]] == 0) zeros -= 1;
        f[l[j]] += 1;
        ++j;

        while (i < j && !zeros) {
            ans = std::min(ans, j - i);
            f[l[i]] -= 1;
            if (f[l[i]] == 0) zeros += 1;
            ++i;
        }
    }

    std::cout << ans << '\n';
}
