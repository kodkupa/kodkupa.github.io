#include <bits/stdc++.h>
#include <cassert>
#define ll long long

using namespace std;

const int BLOCK_SIZE = 230;
const ll INF = 1e18;

int krt_n, n, m, t, q, log_n;
vector<tuple<int, int, int>> edges;
vector<vector<int>> g;
vector<int> value_c, in, out;
vector<vector<int>> parent;

struct SegmentTree {
    int n;
    vector<ll> st, lazy;

    void init(int n) {
        this->n = n;
        st.resize(4 * n + 1);
        lazy.resize(4 * n + 1);
    }

    void apply_lazy(int node, int left, int right, ll plazy) {
        st[node] += plazy;
        lazy[node] += plazy;
    }

    void push_lazy(int node, int left, int right) {
        int mid = (left + right) / 2;
        apply_lazy(node * 2, left, mid, lazy[node]);
        apply_lazy(node * 2 + 1, mid + 1, right, lazy[node]);
        lazy[node] = 0;
    }

    void update(int node, int left, int right, int uleft, int uright, int value) {
        if(left > uright || right < uleft) {
            return;
        }
        if(left >= uleft && right <= uright) {
            apply_lazy(node, left, right, value);
            return;
        }
        push_lazy(node, left, right);
        int mid = (left + right) / 2;
        update(node * 2, left, mid, uleft, uright, value);
        update(node * 2 + 1, mid + 1, right, uleft, uright, value);
        st[node] = min(st[node * 2], st[node * 2 + 1]);
    }

    ll query(int node, int left, int right, int pos) {
        if(left == right) {
            return st[node];
        }
        push_lazy(node, left, right);
        int mid = (left + right) / 2;
        if(pos <= mid) {
            return query(node * 2, left, mid, pos);
        }
        return query(node * 2 + 1, mid + 1, right, pos);
    }

    void update(int l, int r, int v) {
        update(1, 1, n, l, r, v);
    }

    ll query(int pos) {
        return query(1, 1, n, pos);
    }
};

struct Block {
    vector<int> in_of_nodes;
    SegmentTree st;

    void build_block() {
        st.init(in_of_nodes.size());
    }

    void update(int l, int r, int v) {
        int l_here = lower_bound(in_of_nodes.begin(), in_of_nodes.end(), l) - in_of_nodes.begin() + 1;
        int r_here = upper_bound(in_of_nodes.begin(), in_of_nodes.end(), r) - in_of_nodes.begin();
        st.update(l_here, r_here, v);
    }

    ll query(int node) {
        int pos = lower_bound(in_of_nodes.begin(), in_of_nodes.end(), in[node]) - in_of_nodes.begin() + 1;
        assert(in_of_nodes[pos - 1] == in[node]);
        return st.query(pos);
    }
};
vector<Block> blocks;

struct DSU {
    vector<int> parent;

    void init(int n) {
        parent.resize(n + 1);
        for(int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    int get_root(int x) {
        return parent[x] = (parent[x] == x ? x : get_root(parent[x]));
    }

    void join(int a, int b, int c) {
        a = get_root(a);
        b = get_root(b);
        if(a == b) {
            return;
        }

        krt_n++;
        value_c[krt_n] = c;
        g[krt_n].push_back(a);
        g[krt_n].push_back(b);
        parent[a] = parent[b] = krt_n;
    }
}dsu;

void DFS(int node) {
    in[node] = ++t;
    for(int next_node : g[node]) {
        parent[0][next_node] = node;
        DFS(next_node);
    }
    out[node] = t;
}

void precalc() {
    for(int k = 1; (1 << k) <= krt_n; k++) {
        for(int i = 1; i <= krt_n; i++) {
            parent[k][i] = parent[k - 1][parent[k - 1][i]];
        }
    }

    blocks.resize(n / BLOCK_SIZE + 1);
    for(int i = 1; i <= n; i++) {
        blocks[i / BLOCK_SIZE].in_of_nodes.push_back(in[i]);
    }
    for(auto &block : blocks) {
        sort(block.in_of_nodes.begin(), block.in_of_nodes.end());
        block.build_block();
    }
}

int get_top_node(int x, int c) {
    for(int k = log_n; k >= 0; k--) {
        if(parent[k][x] && value_c[parent[k][x]] <= c) {
            x = parent[k][x];
        }
    }
    return x;
}

void update_interval(int l, int r, int v) {
    for(auto &block : blocks) {
        block.update(l, r, v);
    }
}

void update(int x, int k, int v) {
    int top_node = get_top_node(x, k);
    int l = in[top_node], r = out[top_node];
    update_interval(l, r, v);
}

ll query(int l, int r) {
    int block_l = l / BLOCK_SIZE;
    int block_r = r / BLOCK_SIZE;
    ll answer = INF;

    if(block_l == block_r) {
        for(int i = l; i <= r; i++) {
            answer = min(answer, blocks[block_l].query(i));
        }
        return answer;
    }

    int block_l_right = (block_l + 1) * BLOCK_SIZE - 1;
    int block_r_left = block_r * BLOCK_SIZE;
    for(int i = l; i <= block_l_right; i++) {
        answer = min(answer, blocks[block_l].query(i));
    }
    for(int i = block_l + 1; i <= block_r - 1; i++) {
        answer = min(answer, blocks[i].st.st[1]);
    }
    for(int i = block_r_left; i <= r; i++) {
        answer = min(answer, blocks[block_r].query(i));
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> q;
    for(int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        a++; b++; // One-indexing
        edges.emplace_back(c, a, b);
    }

    sort(edges.begin(), edges.end());

    krt_n = n;
    dsu.init(2 * n + 1);
    g.resize(2 * n + 1);
    value_c.resize(2 * n + 1);
    for(auto [c, a, b] : edges) {
        dsu.join(a, b, c);
    }

    log_n = log2(krt_n);
    in.resize(krt_n + 1);
    out.resize(krt_n + 1);
    parent.resize(log_n + 1, vector<int>(krt_n + 1));
    for(int i = 1; i <= krt_n; i++) {
        if(dsu.get_root(i) == i) {
            DFS(i);
        }
    }
    precalc();

    while(q--) {
        int type;
        cin >> type;
        if(type == 1) {
            int x, k, v;
            cin >> x >> k >> v;

            x++; // One-indexing
            update(x, k, v);
        }
        else {
            int l, r;
            cin >> l >> r;

            l++; r++; // One-indexing
            cout << query(l, r) << '\n';
        }
    }

    return 0;
}
