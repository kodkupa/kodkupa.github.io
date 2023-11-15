// @check-accepted: examples Nsmall N1000
// @check-time-limit-exceeded: N10000 no-limits
#include <iostream>
#include <vector>
using namespace std;

int main(){

    int N;
    cin >> N;
    vector<long long> V(N);
    for(auto &x: V)cin >> x;
    
    auto solve = [&](int n){
        int l = n - 1, r = n + 1;
        while(l >= 0 && r < N){
            if(V[n] - V[l] > V[r] - V[n]){
                n = r;
                ++r;
            }else{
                n = l;
                --l;
            }
        }
        return l < 0 ? N-1 : 0;
    };
    
    for(int i = 0; i < N; ++i){
        cout << solve(i) << ' ';
    }
    cout << endl;
}
