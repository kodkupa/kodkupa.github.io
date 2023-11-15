// @check-accepted: examples NSmall NMedium no-limits
#include<iostream>
#include<algorithm>
#include<numeric>
#include<vector>
#include<cassert>
using namespace std;
using ll = long long;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    ll n,k;
    cin>>n>>k;
    
    vector<ll> a(n);
    for(ll& i:a) cin>>i;
    
    ll sum=accumulate(a.begin(), a.end(), 0LL);
    cerr<<sum<<" "<<n*k<<"\n";
    if(sum==n*k) {
        cout<<"0\n";
    }else if(sum<n*k) {
        cout<<"1\n";
    }else {
        ll need_removed=sum-n*k;
        sort(a.begin(), a.end());
        
        ll ans=0;
        for(int i=n-1;i>=0;i--) {
            ll can_remove=min(need_removed, a[i]-1);
            if(can_remove>0) {
                ans++;
                
                need_removed-=can_remove;
                a[i]-=can_remove;
            }
        }
        
        assert(0==need_removed);
        cout<<ans<<"\n";
    }

    return 0;
}
