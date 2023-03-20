#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long ;

#define sz(x) (int)(x).size()
#define xx first
#define yy second

int n, m;

struct edge {
    int to, w, ind;
};

vector<vector<edge>> adj;

vector<vector<int>> dadj;
vector<ll> dp;
const ll mod=1e9+7;
ll calc(int x) {
    if(dp[x]!=-1) return dp[x];
    ll ans=x<2*m;
    for(auto i:dadj[x]) {
        ans+=calc(i);
        ans%=mod;
    }
    return dp[x]=ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    cin>>n>>m;
    
    adj.resize(n+1);

    for(int i=0;i<m;++i) {
        int a,b,c;
        cin>>a>>b>>c;
        adj[a].push_back({b,c,2*i});
        adj[b].push_back({a,c,2*i+1});
    }
    
    int nxt=2*m;
    
    for(int i=1;i<=n;++i) {
        sort(adj[i].begin(), adj[i].end(), [&](const edge& a, const edge& b) -> bool {
            return a.w<b.w;
        });

        vector<int> wlist;
        for(int j=0;j<sz(adj[i]);++j) {
            if(wlist.empty() || wlist.back()!=adj[i][j].w) {
                wlist.push_back(adj[i][j].w);
                
                if(wlist.size()>1 && wlist[sz(wlist)-2]+1==wlist[sz(wlist)-1]) {
                    dadj.resize(nxt+1);
                    for(int L=j-1;L>=0 && wlist[sz(wlist)-2]==adj[i][L].w;L--) {
                        dadj[adj[i][L].ind].push_back(nxt);
                    }
                    for(int R=j;R<sz(adj[i]) && wlist[sz(wlist)-1]==adj[i][R].w;R++) {
                        dadj[nxt].push_back(adj[i][R].ind^1);
                    }
                    
                    ++nxt;
                }
            }
        }
    }
    
    dp.assign(nxt, -1);

    ll ans=-m;
    for(int i=0;i<2*m;++i) {
        ans=(ans+calc(i))%mod;
    }
    
    cout<<ans<<"\n";
    return 0;
}
