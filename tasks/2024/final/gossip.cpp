// @check-accepted: examples NQsmall Nsmall no-limits
// NOTE: it is recommended to use this even if you don't understand the following code.

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int N; cin >> N;
    vector<int> P(N);
    for (int i = 0; i < N; ++i)
        cin >> P[i];
    
    vector<int> cycle(N, -1);
    vector<int> cycle_sz(N, 0);
    vector<int> cycle_pos(N, 0);

    for(int i = 0; i < N; ++i){
        int c = i;
        while(cycle[c] == -1){
            cycle[c] = i;
            c = P[c];
            cycle_pos[c] = cycle_sz[i]++;
        }
    }
    
    int Q; cin >> Q;
    int a,b;
    while(Q--){
        cin >> a >> b;
        if(cycle[a] != cycle[b]){
            cout << -1 << " ";
        }else{
            int c = cycle[a];
            int cs = cycle_sz[c];
            int d = (cycle_pos[a] - cycle_pos[b] + cs) % cs;
            cout << min(d, cs - d) << " ";
        }
    }

    cout << endl;

    return 0;
}
