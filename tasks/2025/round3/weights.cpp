#include <iostream>
#include <vector>
 
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    
    const int bk = 600; // bucket size
    
    vector<long long> differences(n+1), groups(1+(n+1)/bk), frq(n+1);
    differences[0] += 1LL * (n-1) * n / 2;
    groups[0] += 1LL * (n-1) * n / 2;
    
    int cntdistinct = 1;
    vector<int> distinct(bk+bk);
    distinct[1] = 1;
    frq[1] = n;
    for (int i = 1; i <= q; i++) {
        int tp;
        cin >> tp;
        
        if (tp == 1) {
            int a, b;
            cin >> a >> b;
            
            frq[a]--;
            for (int pos = 1; pos <= cntdistinct; pos++) {
                differences[abs(a - distinct[pos])] -= frq[distinct[pos]];
                groups[(abs(a - distinct[pos])) / bk] -= frq[distinct[pos]];
            }
            frq[b]--;
            for (int pos = 1; pos <= cntdistinct; pos++) {
                differences[abs(b - distinct[pos])] -= frq[distinct[pos]];
                groups[(abs(b - distinct[pos])) / bk] -= frq[distinct[pos]];
            }
            for (int pos = 1; pos <= cntdistinct; pos++) {
                differences[abs((a+b) - distinct[pos])] += frq[distinct[pos]];
                groups[(abs((a+b) - distinct[pos])) / bk] += frq[distinct[pos]];
            }
            bool found = 0;
            for (int pos = 1; pos <= cntdistinct; pos++) {
                if (distinct[pos] == a+b) {
                    found = 1;
                }
            }
            if (!found) {
                distinct[++cntdistinct] = a+b;
            }
            frq[a+b]++;
            for (int pos = cntdistinct; pos >= 1; pos--) {
                if (frq[distinct[pos]] == 0) {
                    for (int x = pos; x < cntdistinct; x++) {
                        distinct[x] = distinct[x+1];
                    }
                    cntdistinct--;
                }
            }
            
        }
        else {
            long long k;
            cin >> k;
            for (int i = 0; i <= n/bk; i++) {
                if (k - groups[i] > 0) {
                    k -= groups[i];
                }
                else {
                    for (int pos = i * bk; ; pos++) {
                        k -= differences[pos];
                        if (k <= 0) {
                            cout << pos << '\n';
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
    return 0;
}
