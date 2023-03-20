// @check-accepted: examples bruteforce quadratic all
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
bool can(int digit, int prec, int count_prec, int sum) {
    if (digit == 1 && sum == prec && count_prec == 2) return false;
    int mi = 0;
    int cur = 0;
    if (prec == 0) cur = count_prec;
    for (int i = 0; i < digit; i++) {
        if (cur == 2) {
            mi += 1;
            cur = 0;
        } else if (cur == 1) {
            cur++;
        } else {
            mi += (digit - i) / 3;
            break;
        }
    }
    int ma = 0;
    cur = 0;
    if (prec == 9) cur = count_prec;
    for (int i = 0; i < digit; i++) {
        if (cur == 2) {
            ma += 8;
            cur = 0;
        } else if (cur == 1) {
            ma += 9;
            cur++;
        } else {
            ma += 9 * (digit - i) - (digit - i) / 3;
            break;
        }
    }
    return sum >= mi && sum <= ma;
}
int N;
string S;
void solve() {
    cin >> N >> S;
    int add = max(0, N / 8 - (int)S.size()) + 2;
    S = string(add, '0') + S;
    int pos = S.size() - 1;
    int tot = 0;
    bool trovato = 0;
    for (int i = add; i < S.size(); i++) {
        tot += S[i] - '0';
        if (S[i] == S[i - 1] && S[i] == S[i - 2]) {
            pos = i;
            trovato = 1;
            break;
        }
    }
    if (!trovato && tot == N) {
        for (int i = 0; i < S.size(); i++) {
            if (S[i] != '0') {
                cout << S.substr(i) << '\n';
                return;
            }
        }
        cout << 0 << '\n';
        return;
    }
    for (int i = pos; i >= 0; i--) {
        for (int x = S[i] - '0' + 1; x < 10; x++) {
            S[i] = x + '0';
            tot++;
            if (i >= 2 && S[i] == S[i - 1] && S[i] == S[i - 2]) continue;
            int prec = 1;
            if (i && S[i] == S[i - 1]) prec = 2;

            if (can(S.size() - i - 1, x, prec, N - tot)) {
                for (int j = i + 1; j < S.size(); j++) {
                    bool ok = 0;
                    for (int k = 0; k < 10; k++) {
                        S[j] = k + '0';
                        int prec = 1;
                        if (j >= 2 && S[j] == S[j - 1] && S[j] == S[j - 2]) continue;
                        if (j && S[j - 1] == S[j]) prec = 2;
                        if (can(S.size() - j - 1, k, prec, N - tot - k)) {
                            tot += k;
                            ok = 1;
                            break;
                        }
                    }
                    assert(ok);
                }
                for (int i = 0; i < S.size(); i++) {
                    if (S[i] != '0') {
                        cout << S.substr(i) << '\n';
                        return;
                    }
                }
                return;
            }
        }
        tot -= S[i] - '0';
    }
    cout << "-1\n";
}

int main() {
    int T;
    cin >> T;
    while (T--) solve();
}
