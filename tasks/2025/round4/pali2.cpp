#include <array>
#include <cstddef>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
constexpr ll MN = 200000;

constexpr size_t sz = 4;
constexpr array<ll, sz> mod = {1000000007, 1000000009, 998244353, 990002753};
constexpr array<ll, sz> base = {MN + 4, MN + 7, MN + 15, MN + 27};

struct myhash {
    array<ll, sz> h;
    myhash() { h = base; }
    myhash(ll n) { h.fill(n); }
    myhash operator+(myhash b) {
        myhash ret;
        for (size_t i = 0; i < sz; ++i) {
            ret.h[i] = h[i] + b.h[i];
            if (ret.h[i] > mod[i]) ret.h[i] -= mod[i];
        }
        return ret;
    }
    myhash operator-(myhash b) {
        myhash ret;
        for (size_t i = 0; i < sz; ++i) {
            ret.h[i] = h[i] + mod[i] - b.h[i];
            if (ret.h[i] > mod[i]) ret.h[i] -= mod[i];
        }
        return ret;
    }
    myhash operator*(myhash b) {
        myhash ret;
        for (size_t i = 0; i < sz; ++i) ret.h[i] = (h[i] * b.h[i]) % mod[i];
        return ret;
    }
    bool operator==(const myhash &b) { return h == b.h; }
};
myhash bh;

int main() {
    ll n;
    cin >> n;
    vector<ll> v(n);
    for (auto &x : v) {
        cin >> x;
        x = max(x, 0LL);
    }
    vector<myhash> prefix(n + 1), suffix(n + 1);
    prefix[0] = myhash(0);
    for (int i = 0; i < n; ++i)
        prefix[i + 1] = prefix[i] * bh + myhash(v[i] + 1);
    suffix[n] = myhash(0);
    for (int i = n; i--;) suffix[i] = suffix[i + 1] * bh + myhash(v[i] + 1);
    vector<myhash> zeroPrefix(n + 1), zeroSuffix(n + 1);
    zeroPrefix[0] = myhash(0);
    for (int i = 0; i < n; ++i)
        zeroPrefix[i + 1] = zeroPrefix[i] * bh + (v[i] == 0 ? myhash(1) : 0);
    zeroSuffix[n] = myhash(0);
    for (int i = n; i--;)
        zeroSuffix[i] = zeroSuffix[i + 1] * bh + (v[i] == 0 ? myhash(1) : 0);

    vector<myhash> pow(n + 1);
    pow[0] = myhash(1);
    for (int i = 1; i <= n; ++i) pow[i] = pow[i - 1] * bh;

    ll ans = 1;

    for (int mid = 0; mid < n; ++mid)
        for (int rstart = mid; rstart <= mid + 1 && rstart < n; ++rstart) {
            // binsearch for the closest asymmetrical position
            ll bs = -1;
            for (ll i = 1 << 18; i; i /= 2) {
                ll cur = bs + i;
                ll l = mid - cur;
                ll r = rstart + cur;
                if (l < 0 || r >= n) continue;
                auto lhash = prefix[mid + 1] - prefix[l] * pow[cur + 1];
                auto rhash = suffix[rstart] - suffix[r + 1] * pow[cur + 1];
                if (lhash == rhash) bs = cur;
            }
            ll l = mid - bs;
            ll r = rstart + bs;
            ll x;
            --l;
            ++r;
            if (v[l] == 0)
                x = v[r];
            else if (v[r] == 0)
                x = v[l];
            else {
                ans = max(ans, r - l - 1);
                continue;
            }
            myhash xhash(x);
            for (ll i = 1 << 18; i; i /= 2) {
                ll cur = bs + i;
                ll cl = mid - cur;
                ll cr = rstart + cur;
                if (cl < 0 || cr >= n) continue;
                auto lhash = prefix[mid + 1] - prefix[cl] * pow[cur + 1];
                auto rhash = suffix[rstart] - suffix[cr + 1] * pow[cur + 1];
                auto lxh = zeroPrefix[mid + 1] - zeroPrefix[cl] * pow[cur + 1];
                auto rxh = zeroSuffix[rstart] - zeroSuffix[cr + 1] * pow[cur + 1];
                lhash = lhash + (lxh * xhash);
                rhash = rhash + (rxh * xhash);
                if (lhash  == rhash) bs = cur;
            }
            l = mid - bs;
            r = rstart + bs;
            ans = max(ans, r - l + 1);
        }

    cout << ans << endl;
}
