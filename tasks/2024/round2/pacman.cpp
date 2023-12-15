// @check-accepted: *
#include <algorithm>
#include <iostream>
#include <numeric>
#include <tuple>
#include <unordered_map>
#include <vector>

template <typename T1, typename T2>
struct std::hash<std::pair<T1, T2>> {
    size_t operator()(std::pair<T1, T2> const &p) const {
        return std::hash<T1>()(p.first) ^ std::hash<T2>()(p.second);
    }
};

struct dsu {
    std::vector<size_t> p;
    std::vector<size_t> r;

    dsu(size_t n) : p(n), r(n) { std::iota(p.begin(), p.end(), 0); }

    size_t find(size_t x) { return x == p[x] ? x : p[x] = find(p[x]); }

    bool merge(size_t x, size_t y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (r[x] < r[y]) std::swap(x, y);
        p[y] = x;
        if (r[x] == r[y]) ++r[x];
        return true;
    }
};

using tiii = std::tuple<int, int, int>;

static bool connected(std::vector<tiii> const &v) {
    dsu d(v.size());
    size_t cc = v.size();

    for (size_t i = 0; i < v.size(); ++i) {
        auto const check = [&](int x, int y, int z) {
            tiii t{x, y, z};
            auto it = std::lower_bound(v.begin(), v.end(), t);
            if (it != v.end() && *it == t) {
                auto j = size_t(it - v.begin());
                cc -= d.merge(i, j);
            }
        };

        auto [x, y, z] = v[i];
        check(x + 1, y, z);
        check(x, y + 1, z);
        check(x, y, z + 1);
    }

    return cc == 1;
}

int main() {
    size_t n;
    std::cin >> n;

    std::vector<int> a(n), b(n), c(n);
    for (auto &x : a) std::cin >> x;
    for (auto &x : b) std::cin >> x;
    for (auto &x : c) std::cin >> x;

    std::vector<tiii> v;
    for (size_t i = 0; i < n; ++i) v.emplace_back(a[i], b[i], c[i]);
    std::sort(v.begin(), v.end());

    std::unordered_map<int, std::vector<tiii>> m1;
    std::unordered_map<int, std::vector<tiii>> m2;
    std::unordered_map<int, std::vector<tiii>> m3;
    std::unordered_map<std::pair<int, int>, std::vector<tiii>> m12;
    std::unordered_map<std::pair<int, int>, std::vector<tiii>> m13;
    std::unordered_map<std::pair<int, int>, std::vector<tiii>> m23;

    for (auto [x, y, z] : v) {
        m1[x].emplace_back(x, y, z);
        m2[y].emplace_back(x, y, z);
        m3[z].emplace_back(x, y, z);
        m12[{x, y}].emplace_back(x, y, z);
        m13[{x, z}].emplace_back(x, y, z);
        m23[{y, z}].emplace_back(x, y, z);
    }

    auto const all_connected = [](auto const &m) {
        for (auto const &[x, y] : m) {
            if (!connected(y)) return false;
        }
        return true;
    };

    auto ans = all_connected(m1) && all_connected(m2) && all_connected(m3) &&
               all_connected(m12) && all_connected(m13) && all_connected(m23) &&
               connected(v);

    std::cout << (ans ? "YES" : "NO") << std::endl;
}
