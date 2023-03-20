// @check-accepted: examples one-cat same-row M-small MT-medium can-escape no-limits

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int INF = 2e9;
int M, RJ, CJ, N;
vector<pair<int,int>> pos;

void rotate() {
    int nr = M+1-CJ, nc = RJ;
    RJ = nr, CJ = nc;
    for (auto& p : pos) {
        nr = M+1-p.second, nc = p.first;
        p = {nr, nc};
    }
}
bool can_escape_row1() {
    sort(pos.begin(), pos.end());
    int prevC = 0, nxtC = M+1;
    for (auto p : pos) {
        if (p.first > RJ) break;
        if (p.second < CJ) prevC = max(prevC, p.second);
        else if (p.second > CJ) nxtC = min(nxtC, p.second);
        else return false;
    }
    if (prevC == 0 || nxtC == M+1) return true;
    return nxtC - prevC > 2*(RJ-1)+1;
}

struct event {
    int r, clo, chi;
    bool add;
};

int n;
vector<pair<int,int>> seg;
void propagate(int node) {
    seg[2*node].first += seg[node].second, seg[2*node].second += seg[node].second;
    seg[2*node+1].first += seg[node].second, seg[2*node+1].second += seg[node].second;
    seg[node].second = 0;
}
void update(int l, int r, int inc, int node = 1, int lo = 0, int hi = n) {
    if (r<=lo || l>=hi || l>=r) return;
    if (l==lo && r==hi) {
        seg[node].first += inc;
        seg[node].second += inc;
        return;
    }
    if (seg[node].second != 0) propagate(node);
    int mid = (lo+hi)/2;
    update(l, min(mid,r), inc, 2*node, lo, mid);
    update(max(l, mid), r, inc, 2*node+1, mid, hi);
    seg[node].first = min(seg[2*node].first, seg[2*node+1].first);
}
int query(int l, int r, int node = 1, int lo = 0, int hi = n) {
    if (r<=lo || l>=hi || l>=r) return INF;
    if (l==lo && r==hi) {
        return seg[node].first;
    }
    if (seg[node].second != 0) propagate(node);
    int mid = (lo+hi)/2;
    return min(query(l, min(mid,r), 2*node, lo, mid), query(max(l,mid), r, 2*node+1, mid, hi));
}

bool not_caught(int steps) {
    vector<event> evs(2*N);
    for (int i=0; i<N; ++i) {
        auto& p = pos[i];
        evs[2*i] = {max(0, p.first-steps), max(0, p.second-steps), min(M-1, p.second+steps)+1, true};
        evs[2*i+1] = {min(M, p.first+steps+1), max(0, p.second-steps), min(M-1, p.second+steps)+1, false};    
    }
    sort(evs.begin(), evs.end(), [](const event& ev1, const event& ev2) {
        return ev1.r == ev2.r ? (ev1.clo == ev2.clo ? (1-ev1.add < 1-ev2.add) : ev1.clo < ev2.clo) : ev1.r < ev2.r;
    });
    
    vector<int> pts(2*N+2);
    for (int i=0; i<N; ++i) {
        auto& p = pos[i];
        pts[2*i] = max(0, p.second-steps), pts[2*i+1] = min(M-1, p.second+steps)+1;
    }
    pts[2*N] = max(0,CJ-steps), pts[2*N+1] = min(M-1,CJ+steps)+1;
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    map<int,int> ptids;
    for (int i=0; i<(int)pts.size(); ++i) ptids[pts[i]] = i;

    for (n=1; n<=2*N+2; n<<=1);
    seg.assign(2*n, {0,0});
    int ql = ptids[max(0,CJ-steps)], qr = ptids[min(M-1,CJ+steps)+1];
    for (int i=0; i<2*N; ++i) {
        int curr = evs[i].r;

        if (curr > min(M-1,RJ+steps)) return query(ql,qr) == 0;
        if (curr > max(0,RJ-steps) && query(ql,qr) == 0) return true;

        int l = ptids[evs[i].clo], r = ptids[evs[i].chi];
        update(l, r, evs[i].add ? 1 : -1);
        while (i+1 < 2*N && evs[i+1].r == curr) {
            ++i;
            l = ptids[evs[i].clo], r = ptids[evs[i].chi];
            update(l, r, evs[i].add ? 1 : -1);
        }
    }
    if (evs.back().r >= RJ-steps && query(ql,qr) == 0) return true;

    return false;
}

void solve() {
    cin >> RJ >> CJ >> N;
    pos.resize(N);
    for (int i=0; i<N; ++i) cin >> pos[i].first >> pos[i].second;

    int best_escape = INF;
    for (int o=0; o<4; ++o) {
        if (can_escape_row1()) best_escape = min(best_escape, RJ-1);
        rotate();
    }
    if (best_escape < INF) {
        cout << "ESCAPED " << best_escape << '\n';
        return;
    }

    --RJ, --CJ;
    for (auto& p : pos) --p.first, --p.second;
    int lo=0, hi=M/2+2;
    while (lo+1 < hi) {
        int mid = (lo+hi)/2;
        if (not_caught(mid)) lo = mid;
        else hi = mid;
    }
    cout << "CAUGHT " << hi << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> M >> T;
    while (T--)
        solve();
    
    return 0;
}
