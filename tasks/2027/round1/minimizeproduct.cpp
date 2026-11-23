// Full solution with geometric series, O(N + Q log K).
//
// Let m = r - l + 1. The [l, r] subarray has T = m(m+1)/2 subarrays: O of odd length and
// E = T - O of even length.
//
// If [l, r] contains a 0, the product is always 0, so every sequence of at most k flips is
// optimal: 1 + T + T^2 + ... + T^k ways.
//
// Otherwise the smallest possible product is -|product|. A flip changes the sign of the product
// exactly when it flips an odd number of elements, so only the parity of the number of odd-length
// flips matters. Among the T^j sequences of j flips,
//   ((E + O)^j + (E - O)^j) / 2 contain an even number of odd-length flips, and
//   ((E + O)^j - (E - O)^j) / 2 contain an odd number of them.
// Summing for j = 0..k gives two geometric series. If the product is already negative, we need an
// even number of odd-length flips, otherwise an odd number. (If k = 0 and the product is not
// negative, nothing can be changed: the only way is the empty sequence.)

#include <iostream>
#include <vector>

using namespace std;

const long long MOD = 998244353;

long long power(long long a, long long e) {
    long long result = 1;
    a %= MOD;
    while (e > 0) {
        if (e % 2 == 1)
            result = result * a % MOD;
        a = a * a % MOD;
        e /= 2;
    }
    return result;
}

// 1 + a + a^2 + ... + a^k modulo MOD
long long geometric(long long a, long long k) {
    a = (a % MOD + MOD) % MOD;
    if (a == 1)
        return (k + 1) % MOD;
    // (a^(k+1) - 1) / (a - 1), dividing by the modular inverse
    return (power(a, k + 1) - 1 + MOD) % MOD * power(a - 1, MOD - 2) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    // neg[i], zero[i]: number of negative / zero elements among the first i elements
    vector<int> neg(N + 1, 0), zero(N + 1, 0);
    for (int i = 0; i < N; i++) {
        long long v;
        cin >> v;
        neg[i + 1] = neg[i] + (v < 0);
        zero[i + 1] = zero[i] + (v == 0);
    }

    const long long INV2 = (MOD + 1) / 2;  // the inverse of 2
    for (int i = 0; i < Q; i++) {
        long long l, r, k;
        cin >> l >> r >> k;

        long long m = r - l + 1;
        long long T = m * (m + 1) / 2;
        long long h = (m + 1) / 2;              // number of odd lengths in 1..m
        long long O = h * (m + 1) - h * h;      // sum of m - len + 1 for odd len
        long long E = T - O;

        long long all = geometric(T, k);
        long long answer;
        if (zero[r + 1] - zero[l] > 0) {
            answer = all;
        } else if (k == 0) {
            answer = 1;
        } else {
            long long diff = geometric(E - O, k);
            if ((neg[r + 1] - neg[l]) % 2 == 1)
                answer = (all + diff) % MOD * INV2 % MOD;        // keep the sign
            else
                answer = (all - diff + MOD) % MOD * INV2 % MOD;  // change the sign
        }
        cout << answer << "\n";
    }
    return 0;
}
