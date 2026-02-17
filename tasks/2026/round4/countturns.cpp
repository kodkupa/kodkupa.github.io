// @check-accepted: examples ReallySmall NxK NsqrtN O1
#include <iostream>

using namespace std;

bool solve_fast(long long n, long long k, long long l){ // true if Alice wins
    long long cnt = (n + (l - 1)) / l + n / l; // # of i<=n, i=0,1 mod l
    if(n % l == 0 || n % l == 1){
        return cnt % k == 0;
    }
    else {
        return cnt % k == 0 || (cnt + 1) % k == 0;
    }
}

int main() {
    int t; cin>>t;
    while(t--){
        int n, k; cin>>n>>k;
        cout<<(solve_fast(n, k, k + 1) ? "Alice" : "Bob")<<"\n";
    }

}
