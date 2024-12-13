#include <bits/stdc++.h>

using namespace std;
int n;
int msb[1005], sol[1005];

int ask(int a, int b) {
    cout << "? " << a << ' ' << b << endl;
    int ans;
    cin >> ans;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    int maxim = 0;
    for (int i = 1; i <= n; i++) {
        int x = ask(i, i);
        msb[i] = x;
        maxim = max(maxim, msb[i]);
    }
    for (int bit = 0; bit <= maxim; bit++) {
        int who = 0;
        for (int i = 1; i <= n; i++)
            if (msb[i] == bit) {
                who = i;
                break;
            }
        for (int i = 1; i <= n; i++) {
            int x = ask(who, i);
            if (x == bit)
                sol[i] += (1 << bit);
        }
    }
    cout << "! ";
    for (int i = 1; i <= n; i++)
        cout << sol[i] << ' ';
    cout << endl;
    return 0;
}
