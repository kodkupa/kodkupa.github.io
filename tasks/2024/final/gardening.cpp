#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>
#include <cassert>

using namespace std;
using ll = long long ;
const int MAXN=200001;
const int LG=18;

#define LOG(x) cerr<<(#x)<<" = "<<x<<"\n";

int par[MAXN], opened[MAXN]; //1->open 0->closed
ll cost[MAXN];

vector<int> adj[MAXN];

int n,q;
int eL[MAXN], eR[MAXN], ind, root, lvl[MAXN];
ll dp_close[MAXN], dp_sum[MAXN];
void dfs(int x) {
    eL[x]=ind++;
    dp_close[x]=(opened[x]?cost[x]:0);
    for(auto i:adj[x]) {
        lvl[i]=lvl[x]+1;
        dfs(i);
        dp_sum[x]+=dp_close[i];
    }
    if(adj[x].size()>0) dp_close[x]=min(dp_close[x], dp_sum[x]);

    eR[x]=ind-1;
}

ll open_cost(ll x) {
    return (opened[x]?0:cost[x]);
}

struct par_info {
    int par;
    int bef;
    ll cost_close;
    ll cost_open;

    par_info() : par(0), bef(0), cost_close(0LL), cost_open(0LL) {}
};

// a is higher than b
par_info operator+(par_info& a, par_info& b) { 
    par_info res; 
    res.par=a.par;
    res.bef=a.bef;
    res.cost_close=a.cost_close+b.cost_close+dp_sum[b.par]-dp_close[b.bef];
    res.cost_open=a.cost_open+b.cost_open+open_cost(b.par);
    return res;
}

par_info dp[MAXN][LG];

void init_lca() {
    for(int i=1;i<=n;++i) {
        dp[i][0].par=par[i];
        dp[i][0].bef=i;
        dp[i][0].cost_close=0;
    }

    for(int j=1;j<LG;++j) {
        for(int i=1;i<=n;++i) {
            dp[i][j]=dp[dp[i][j-1].par][j-1]+dp[i][j-1];
        }
    }
}

int get_lca(int x, int y) {
    if(lvl[x]>lvl[y]) swap(x,y);
    for(int i=LG-1;i>=0;i--) {
        int py=dp[y][i].par;
        if(py>0 && lvl[py]>lvl[x]) y=py;
    }
    if(lvl[x]<lvl[y]) y=dp[y][0].par;
    if(x==y) return x;
    for(int i=LG-1;i>=0;i--) {
        int px=dp[x][i].par;
        int py=dp[y][i].par;
        if(px>0 && py>0 && px!=py) {
            x=px; y=py;
        }
    }
    return dp[x][0].par;
}

// a is higher than b
// get the par_info for the nodes on a chain from a to b
par_info get_chain_ans(int a, int b) {
    par_info res;
    for(int i=LG-1;i>=0;i--) {
        int pb=dp[b][i].par;
        if(lvl[pb]>=lvl[a]) {
            res=dp[b][i]+res;
            b=pb;
        }
    }
    return res;
}

bool is_anc(int a, int b) {
    return eL[a]<=eL[b] && eL[b]<=eR[a];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>q; 
    for(int i=1;i<=n;++i) { 
        cin>>par[i];
        par[i]++;
        if(par[i]==0) root=i;
        else adj[par[i]].push_back(i);
    }
    for(int i=1;i<=n;++i) {
        cin>>cost[i];
    }
    
    for(int i=1;i<=n;++i) {
        cin>>opened[i];
    }

    lvl[root]=1;
    dfs(root);
    init_lca();

    for(int i=0;i<q;++i) {
        int cnt;
        cin>>cnt;
        if(cnt==0) {
            cout<<dp_close[root]<<"\n";
        }else {
            vector<int> need_water(cnt);
            for(int i=0;i<cnt;++i) {
                cin>>need_water[i];
                need_water[i]++;
            }
            need_water.push_back(root);
            sort(need_water.begin(), need_water.end(), [&](int x, int y) -> bool {
                return eL[x]<eL[y];
            });
            for(int i=1;i<cnt+1;++i) {
                int lca=get_lca(need_water[i-1], need_water[i]);
                need_water.push_back(lca);
            }
            sort(need_water.begin(), need_water.end());
            need_water.resize(distance(need_water.begin(), unique(need_water.begin(), need_water.end())));
            sort(need_water.begin(), need_water.end(), [&](int x, int y) -> bool {
                return eL[x]<eL[y];
            });


            vector<int> stk;
            stk.push_back(root);
            assert(need_water[0]==root);
            need_water.erase(need_water.begin());
            ll ans=open_cost(root)+dp_sum[root];
            for(int i:need_water) { //poor man's dfs on the lca tree
                while(!is_anc(stk.back(), i)) {
                    stk.pop_back();
                }
                par_info chain=get_chain_ans(stk.back(), i);

                ans+=chain.cost_open;
                ans+=chain.cost_close;
                ans-=dp_close[chain.bef];

                ans+=open_cost(i)+dp_sum[i];
                stk.push_back(i);
            }
            cout<<ans<<"\n";
        }
    }
    return 0;
}
