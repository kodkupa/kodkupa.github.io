#include <iostream>
#include <vector>
 
using namespace std;
 
int main() {
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        
        vector<int> v(n+1);
        for (int i = 1; i <= n; i++) {
            cin >> v[i];
        }
        
        int max_sets = 0;
        for (int warmup = 0; warmup <= n; warmup++) {
            int sets = 0;
            int score_1 = 0;
            int score_2 = 0;
            for (int pos = warmup + 1; pos <= n; pos++) {
                if (v[pos] == 1) {
                    score_1++;
                }
                else {
                    score_2++;
                }
                if (score_1 >= 4 && score_1 - score_2 >= 2) {
                    sets++;
                    score_1 = 0;
                    score_2 = 0;
                }
                if (score_2 >= 4 && score_2 - score_1 >= 2) {
                    sets++;
                    score_1 = 0;
                    score_2 = 0;
                }
            }
            max_sets = max(max_sets, sets);
        }
        
        cout << max_sets << '\n';
    }
    return 0;
}

