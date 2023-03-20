// @check-accepted: examples N<=8 N<=100 N<=5000 N<=1000000
#include<iostream>
#include<algorithm>
#include<map>
#include<vector>
#include<numeric>
#include<queue>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    vector<int> p(n);
    for(int i=0;i<n;++i) {
        cin>>p[i];
    }

    int g=0;
    for(int i=0;i<n;++i) {
        g=gcd(g, abs(p[i]-(i+1)));
    }

    int cost=n;
    vector<int> had(n+1);
    for(int i=0;i<n;++i) {
        if(!had[p[i]]) {
            int akt=p[i];
            cost--;

            while(!had[akt]) {
                had[akt]=1;
                akt=p[akt-1];
            }
        }
    }

    vector<int> ans;
    if(g==0) {
        for(int i=1;i<=n;++i) {
            ans.push_back(i);
        }
    }else {
        for(int k=1;k*k<=g;++k) {
            if(g%k==0) {
                ans.push_back(k);
                if(k!=g/k) ans.push_back(g/k);
            }
        }
        
        sort(ans.begin(), ans.end());
    }

    vector<int> res(n+1, -1);
    for(auto i:ans) res[i]=cost;
    for(int i=1;i<=n;++i) cout<<res[i]<<" \n"[i==n];

    return 0;
}
