#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
//#pragma GCC optimize("Ofast,unroll-loops")
using namespace std;
typedef long long ll;
const ll NMAX=2e5+5,inf=1e16;

void tc(){
    ll n;
    string s;
    cin>>n>>s;
    vector<ll> segments={0};
    ll ans=0;
    for(ll i=0;i<n;i++){
        if(s[i]=='.') segments.back()++;
        else if(segments.back())
            segments.emplace_back();
    }
    if(segments.back()==0) segments.pop_back();
    if(segments.empty()){
        cout<<"0 0\n";
        return;
    }
    sort(segments.begin(),segments.end());
    for(ll i=segments.size()-1;i>=0;i--){
        ans=max(ans,segments[i]/2+(ll)segments.size()-i);
    }
    cout<<segments.size()<<' '<<ans<<'\n';
}
int main()
{
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ll t; cin>>t; while(t--)
        tc();
}
