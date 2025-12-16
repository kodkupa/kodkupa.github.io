#include <iostream>
#include <utility>
#include <vector>
#include <set>

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
const ll NMAX=1e6+5,MOD=998244353;
struct matrix{
    ll data[3][3]{};
};
matrix operator * (const matrix& a, const matrix& b){
    matrix p;
    for(ll i=0;i<3;i++){
        for(ll k=0;k<3;k++){
            for(ll j=0;j<3;j++)
                p.data[i][k]+=a.data[i][j]*b.data[j][k];
            p.data[i][k]%=MOD;
        }
    }
    return p;
}
matrix binPow(matrix x, ll y){
    matrix ans;
    ans.data[0][0]=ans.data[1][1]=ans.data[2][2]=1;
    for(;y;y>>=1,x=x*x)
        if(y&1)
            ans=ans*x;
    return ans;
}
set<pll> blocked;
set<ll> careful;
int main(){
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    ll n,m;
    cin>>n>>m;
    for(ll i=0;i<m;i++){
        ll u,v;
        cin>>u>>v;
        blocked.insert({u,v});
        for(ll j=u;j<=u+3 && j<=n;j++) careful.insert(j);
    }
    matrix transition,dp;
    dp.data[0][2]=1;
    transition.data[1][0]=transition.data[2][1]=transition.data[0][2]=transition.data[1][2]=transition.data[2][2]=1;
    careful.insert(1);
    careful.insert(n);
    for(auto it=careful.begin();next(it)!=careful.end();it++){
        ll curr=*it,nxt=*next(it);
        if(nxt>curr+1) dp=dp*binPow(transition,nxt-curr);
        else{
            matrix transition2=transition;
            if(blocked.count({nxt-1,nxt})) transition2.data[2][2]=0;
            if(blocked.count({nxt-2,nxt})) transition2.data[1][2]=0;
            if(blocked.count({nxt-3,nxt-1}) || blocked.count({nxt-2,nxt-1}) || blocked.count({nxt-2,nxt})) transition2.data[0][2]=0;
            dp=dp*transition2;
        }
    }
    cout<<dp.data[0][2]<<"\n";
    return 0;
}
