#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
#include<array>
using namespace std;
using ll = long long;
const ll MAXN=100010;
const ll MAXVAL=1e9;
int n,k;
int a[MAXN], b[MAXN];
int nxt[MAXN];
vector<int> adj[MAXN];

void read() {
    cin>>n>>k;
    for(int i=0;i<n;++i) {
        cin>>a[i];
    }
    for(int i=0;i<n;++i) {
        cin>>b[i];
    }
    
    a[n]=*max_element(a, a+n)+1;
    b[n]=0;

    stack<int, vector<int>> st;
    st.push(n);
    for(int i=n-1;i>=0;i--) {
        while(!st.empty() && a[st.top()]<=a[i]) st.pop();
        nxt[i]=st.top();
        adj[nxt[i]].push_back(i);
        st.push(i);
    }
}

struct range {
    ll l, r;
    range operator+(int x) const {
        return {l+x, r+x};
    }
    range operator|(const range& other) const {
        return range{min(l, other.l), max(r, other.r)};
    }
};

range add_ranges(range& a, range& b) {
    return range{a.l+b.l, a.r+b.r};
}

using Res = pair<ll, range>;
Res operator+(const Res& one, const Res& other) {
    if(one.first>other.first) return one;
    else if(one.first<other.first) return other;
    return {one.first, one.second|other.second};
}

Res calc(ll lambda) {
    vector<array<Res,2>> dp(n+1);
    Res minf={-(1LL<<60), {-1,-1}}, zero={0, {0,0}};
    for(int i=0;i<=n;++i) {
        array<Res,2> dp_prv={zero, minf};
        array<Res,2> dp_nxt;
        for(int j:adj[i]) {
            dp_nxt={minf, minf};

            dp_nxt[0] = dp_nxt[0] + Res{
                dp_prv[0].first + dp[j][0].first,
                add_ranges(dp_prv[0].second, dp[j][0].second)
            };
            dp_nxt[0] = dp_nxt[0] + Res{
                dp_prv[0].first + dp[j][1].first,
                add_ranges(dp_prv[0].second, dp[j][1].second)
            };
            dp_nxt[0] = dp_nxt[0] + Res{
                dp_prv[1].first + dp[j][1].first,
                add_ranges(dp_prv[1].second, dp[j][1].second)
            };
            dp_nxt[0] = dp_nxt[0] + Res{
                dp_prv[1].first + dp[j][0].first,
                add_ranges(dp_prv[1].second, dp[j][0].second)
            };
            

            dp_nxt[1] = dp_nxt[1] + Res{
                dp_prv[0].first + dp[j][1].first,
                add_ranges(dp_prv[0].second, dp[j][1].second)
            };
            dp_nxt[1] = dp_nxt[1] + Res{
                dp_prv[1].first + dp[j][1].first,
                add_ranges(dp_prv[1].second, dp[j][1].second)
            };
            dp_nxt[1] = dp_nxt[1] + Res{
                dp_prv[1].first + dp[j][0].first,
                add_ranges(dp_prv[1].second, dp[j][0].second)
            };

            swap(dp_nxt, dp_prv);
        }
        dp[i][0] = dp_prv[0];
        dp[i][1] = Res{dp_prv[0].first+b[i]-lambda, dp_prv[0].second+1};
        dp[i][1] = dp[i][1] + Res{dp_prv[1].first+b[i], dp_prv[1].second};
        //cerr<<dp[i][0].first<<" "<<dp[i][1].first<<" "<<b[i]<<" "<<adj[i].size()<<"\n";
    }
    //cerr<<dp[n][0].second.l<<" "<<dp[n][0].second.r<<" "<<dp[n][0].first<<"\n";
    return dp[n][0];
}

void solve() {

    ll L=-n*MAXVAL, R=n*MAXVAL;
    while(L<R) {
        ll mid=(L+R+1)/2;
        //cerr<<L<<" "<<R<<"\n";
        auto curr=calc(mid);
        if(curr.second.l<=k && k<=curr.second.r) {
            L=R=mid;
            break ;
        }
        if(curr.second.r<k) R=mid-1;
        else L=mid;
    } 
    auto ans=calc(L);
    cout<<ans.first+L*k<<"\n";
    /*
    for(int i=-3*n;i<=3*n;++i) {
        auto x=calc(i);
        cerr<<"lambda="<<i<<": value="<<x.first<<" l_k="<<x.second.l<<" r_k="<<x.second.r<<"\n";
    }
    */
}

int main() {
    read();
    solve();
    return 0;
}