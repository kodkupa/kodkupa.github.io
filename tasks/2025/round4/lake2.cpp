// @check-accepted: examples quadratic linear segment no-limits
#include <bit>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr ll blk = 64;

inline ull mask(ll sz) {
    if (sz >= blk) return -1ULL;
    return (1ULL << sz) - 1;
}

int pool[2100000];
ull base_pool[600000];
int p_id = 0;
int bp_id = 0;

struct segment {
    int* sum;
    int* lazy;
    ull* base;
    int n;
    segment(int _n) {
        n = 1;
        while (n * blk < _n) n *= 2;
        sum = &pool[p_id];
        p_id += n * 2;
        lazy = &pool[p_id];
        p_id += n * 2;
        base = &base_pool[bp_id];
        bp_id += n;
    }

    inline void propagate(int node, int sz) {
        if (lazy[node]) {
            lazy[node] = 0;
            if (node * 2 < n) {
                sum[node * 2] = sz / 2 - sum[node * 2];
                lazy[node * 2] ^= 1;
                sum[node * 2 + 1] = sz / 2 - sum[node * 2 + 1];
                lazy[node * 2 + 1] ^= 1;
            } else {
                base[node * 2 - n] ^= mask(blk);
                sum[node * 2] = __popcount(base[node * 2 - n]);
                base[node * 2 + 1 - n] ^= mask(blk);
                sum[node * 2 + 1] = __popcount(base[node * 2 + 1 - n]);
            }
        }
    }

    int qry() { return sum[1]; }

    int ul, ur;
    void upd(int node, int l, int r) {
        if (ul >= r || ur <= l) return;
        if (node >= n) {
            base[node - n] ^= (ur >= r ? -1ULL : mask(ur % blk));
            base[node - n] ^= (ul < l ? 0ULL : mask(ul % blk));
            sum[node] = __popcount(base[node - n]);
            return;
        }
        if (ul <= l && r <= ur) {
            lazy[node] ^= 1;
            sum[node] = r - l - sum[node];
            return;
        }
        propagate(node, r - l);
        int mid = (l + r) / 2;
        upd(node * 2, l, mid);
        upd(node * 2 + 1, mid, r);
        sum[node] = sum[node * 2] + sum[node * 2 + 1];
    }
    void upd(int l, int r) {
        ul = l;
        ur = r;
        upd(1, 0, n * blk);
    }
};

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int n, m, Q;
    cin >> n >> m >> Q;
    ll ans = 0;
    vector<segment> vert;
    vert.reserve(m + 1);
    for (int i = 0; i <= m; ++i) vert.emplace_back(segment(n));
    vector<segment> hor;
    hor.reserve(n + 1);
    for (int i = 0; i <= n; ++i) hor.emplace_back(segment(m));
    for (int q = 0; q < Q; ++q) {
        int x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        --x1;
        --y1;
        ans -= vert[y1].qry();
        ans -= vert[y2].qry();
        vert[y1].upd(x1, x2);
        vert[y2].upd(x1, x2);
        ans += vert[y1].qry();
        ans += vert[y2].qry();

        ans -= hor[x1].qry();
        ans -= hor[x2].qry();
        hor[x1].upd(y1, y2);
        hor[x2].upd(y1, y2);
        ans += hor[x1].qry();
        ans += hor[x2].qry();

        cout << ans << endl;
    }
}
