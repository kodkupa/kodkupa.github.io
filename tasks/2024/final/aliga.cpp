#include <bits/stdc++.h>

using namespace std;

struct node{
    vector<pair<int, int>> to;
    int id;
};

struct data_vec{
    vector<int> v, upd;
    int zero = 0, cur = 0;
    data_vec(int n = 0) : v(n*2 + 1), upd(n*2+1), zero(n) {}
    
    bool check(int i) { return i + zero >= 0 && i + zero < (int)v.size(); }

    int get(int i) { 
        if(!check(i)) return 0;
        return upd[i + zero] == cur ? v[i + zero] : 0;
    }
    void set(int i, int x) {
        if(!check(i)) return;
        v[i + zero] = x; upd[i + zero] = cur;
    }
    void add(int i, int x) {
        if(!check(i)) return;
        if(upd[i+zero] != cur) set(i, 0);
        v[i + zero] += x;
    }
    void init() { cur++; }
};

data_vec cnt(100000);
vector<int> sz;
vector<bool> vis;
long long ans = 0;
int mult = 1;

int get_sz(const vector<node> &g, int x, int p = -1){
    sz[x] = 1;
    for(auto [y, _] : g[x].to){
        if(!vis[y] && y != p){
            sz[x] += get_sz(g, y, x);
        }
    }
    return sz[x];
}

int get_c(const vector<node> &g, int x, int n, int p = -1){
    for(auto [y, _] : g[x].to){
        if(!vis[y] && y != p && sz[y]*2 > n){
            return get_c(g, y, n, x);
        }
    }
    return x;
}

void dfs1(const vector<node> &g, int x, int d = 0, int p = -1){
    int val = d - g[x].id * mult;
    ans += cnt.get(-val);
    for(auto [y, w] : g[x].to){
        if(!vis[y] && y != p){
            dfs1(g, y, d+w, x);
        }
    }
}

void dfs2(const vector<node> &g, int x, int d = 0, int p = -1){
    int val = d - g[x].id * mult;
    cnt.add(val, 1);
    for(auto [y, w] : g[x].to){
        if(!vis[y] && y != p){
            dfs2(g, y, d+w, x);
        }
    }
}

void centroid_decomposition(const vector<node> &g, int c){
    cnt.init();
    c = get_c(g, c, get_sz(g, c));
    
    vis[c] = true;

    cnt.add(-g[c].id * mult, 1);
    for(auto [y, w] : g[c].to){
        if(!vis[y]){
            dfs1(g, y, w);
            dfs2(g, y, w);
        }
    }
    for(auto [y, _] : g[c].to){
        if(!vis[y]){
            centroid_decomposition(g, y);
        }
    }
}

pair<int, int> dfs_compr(const vector<node> &g, vector<node> &ng, int x, int cap, int d = 0, int p = -1){
    vector<pair<int, int>> child;
    for(auto [y, w] : g[x].to){
        if(y != p){
            auto tmp = dfs_compr(g, ng, y, cap, d + w, x);
            if(tmp.first != -1) child.push_back(tmp);
        }
    }
    if(child.size() > 1 || g[x].id <= cap){
        int cur = (int)ng.size();
        ng.push_back(node());
        ng[cur].id = g[x].id;
        for(auto [y, w] : child){
            ng[cur].to.emplace_back(y, w - d);
            ng[y].to.emplace_back(cur, w - d);
        }
        return {cur, d};
    }
    return child.empty() ? pair<int, int>{-1, -1} : child[0];
}

vector<node> compress(const vector<node> &g, int cap){
    vector<node> res;
    auto tmp = dfs_compr(g, res, 0, cap);
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;

    vector<node> g(n);
    for(int i = 0; i < n; i++) g[i].id = i;
    for(int i = 0; i < n-1; i++){
        int a, b;
        cin>>a>>b;
        g[a].to.emplace_back(b, 1);
        g[b].to.emplace_back(a, 1);
    }

    vis.assign(g.size(), false);
    int last_cap = n;
    for(int i = 1; i <= n; i++){
        if(n / i != last_cap){
            g = compress(g, n / i);
            last_cap = n / i;
        }
        vis.assign(g.size(), false);
        sz.resize(g.size());
        mult = i;
        centroid_decomposition(g, 0);
    }

    cout << ans << '\n';

    return 0;
}