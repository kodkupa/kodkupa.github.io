/*
(Here the two trees are tree A and tree B)
For every weighted edge (x, y, w), store it in node x in tree A, also do the same for all the queries, store query (u, v) in node u in tree A.
Do a tree traversal in tree A, when entering a node, activate the weighted edges starting from it, when leaving the node deactivate them.
       -When activating edge (x, y, w), increment all the values of all nodes in the subtree of y in tree B, with the weight of the edge (w) using a fenwick tree or segment tree (or any range update data structure). (Initially every node value is 0.)
       -When deactivating you need to decrement.
That way when we reach node u in tree A, the answer for any query (u, v) will be the value of node v in tree B.
Proof:  This is the sum of weights of edges (x, y, w), where x is an ancestor of u (, because only these edges are activated), and y is an ancestor of v, because v must be on the subtree of y if it's value increased.

Subtask1: brute force
Subtask2: requires the tree traversal idea, but you can iterate through the ancestors of node u or v (in the less deep tree)
Subtask3: one of the trees is a bamboo, so do not need to know the subtree update, just simple range update
Subtask4: Full solution
*/

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

struct fenwick_tree{ //zero indexed
    vector<long long> val;
    void init(int n) { val.assign(n+1, 0); }
    void update(int x, long long c){ 
        for(int i = x+1; i < (int)val.size(); i += (i&(-i))){
            val[i] += c;
        }
    }
    void update(int l, int r, long long c) { update(l, c); update(r, -c); }
    long long query(int x){
        long long res = 0;
        for(int i = x+1; i > 0; i -= (i&(-i))){
            res += val[i];
        }
        return res;
    }
};

vector<vector<int>> ga, gb;
vector<vector<pair<int, int>>> edges, querys;
vector<int> tree_size, pos;
vector<long long> ans;
fenwick_tree ft;

int cur_pos = 0;
int dfs1(int x){
    tree_size[x] = 0;
    for(int y : gb[x]){
        tree_size[x] += dfs1(y);
    }
    pos[x] = cur_pos++;
    return tree_size[x] + 1;
}

void dfs2(int x){
    for(auto [y, w] : edges[x]){
        ft.update(pos[y] - tree_size[y], pos[y] + 1, w);
    }
    for(auto [y, i] : querys[x]){
        ans[i] = ft.query(pos[y]);
    }
    for(int y : ga[x]){
        dfs2(y);
    }
    for(auto [y, w] : edges[x]) {
        ft.update(pos[y] - tree_size[y], pos[y] + 1, -w);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;
    ga.resize(n);
    edges.resize(n);
    querys.resize(n);
    for(int i = 1; i < n; i++){
        int x;
        cin>>x;
        ga[x-1].push_back(i);
    }

    int m;
    cin>>m;
    gb.resize(m);
    pos.resize(m);
    tree_size.resize(m);
    ft.init(m);
    for(int i = 1; i < m; i++){
        int x;
        cin>>x;
        gb[x-1].push_back(i);
    }

    int k;
    cin>>k;
    for(int i = 0; i < k; i++){
        int x, y, w;
        cin>>x>>y>>w;
        edges[x-1].emplace_back(y-1, w);
    }

    int q;
    cin>>q;
    ans.resize(q);
    for(int i = 0; i < q; i++){
        int x, y;
        cin>>x>>y;
        querys[x-1].emplace_back(y-1, i);
    }

    dfs1(0);
    dfs2(0);

    for(long long x : ans) cout<<x<<'\n';

    return 0;
}
