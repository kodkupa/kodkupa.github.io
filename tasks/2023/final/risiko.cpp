#include <algorithm>
#include <chrono>
#include <iostream>
#include <queue>
#include <random>
#include <set>
#include <vector>
typedef long long ll;
using namespace std;
#define TL 3.96
mt19937 rng(42);
struct Timer {
    timespec start;
    double lapse;
    Timer() {
    }
    void begin() {
        clock_gettime(CLOCK_REALTIME, &start);
    }
    double stopwatch() {
        timespec end;
        clock_gettime(CLOCK_REALTIME, &end);
        double sec = end.tv_sec - start.tv_sec;
        double nsec = end.tv_nsec - start.tv_nsec;
        lapse = sec + nsec / 1000000000;
        return lapse;
    }
} timer;

int N, K;
vector<vector<int>> adj;
vector<ll> w;
vector<int> initial_sol() {
    queue<int> q;
    vector<int> color(N, K);
    vector<ll> color_w(K, 0);
    vector<bool> vis(N, 0);
    set<int> s;
    for (int i = 0; i < N; ++i) s.insert(i);
    while (!s.empty()) {
        q.push(*s.begin());
        while (!q.empty()) {
            int n = q.front();
            q.pop();
            if (vis[n]) continue;
            vis[n] = 1;
            s.erase(n);
            vector<int> is_adj(K, 0);
            for (auto x : adj[n]) {
                if (color[x] < K) is_adj[color[x]] = 1;
                if (!vis[x]) q.push(x);
            }
            ll min = 1e18;
            for (int i = 0; i < K; ++i) {
                if (!is_adj[i] && color_w[i] < min) {
                    min = color_w[i];
                    color[n] = i;
                }
            }
            color_w[color[n]] += 1;
        }
    }
    return color;
}
vector<int> fix_sol(vector<int> cur) {
    vector<int> tot[K];
    for (int i = 0; i < N; i++) tot[cur[i]].push_back(i);
    int target = N / K;
    vector<int> big;
    for (int i = 0; i < K; ++i) {
        if (tot[i].size() > target) {
            big.push_back(i);
        }
    }
    while (1) {
        bool ok = 1;
        for (int i = 0; i < K; ++i) {
            if (tot[i].size() < target) {
                ok = 0;
                int k = rng() % big.size();
                int pos = rng() % tot[big[k]].size();
                int val = tot[big[k]][pos];
                bool vicini = 0;
                for (auto x : adj[val]) {
                    if (cur[x] == i) vicini = 1;
                }
                if (vicini) continue;
                cur[val] = i;
                tot[i].push_back(val);
                swap(tot[big[k]].back(), tot[big[k]][pos]);
                tot[big[k]].pop_back();
                if (tot[big[k]].size() == target) {
                    swap(big[k], big.back());
                    big.pop_back();
                }
            }
        }
        if (ok) break;
    }
    return cur;
}
vector<int> ans;
ll best = 0;

vector<int> cur_color;
vector<ll> tot;
ll cur_score = 0;
bool ok(int pos) {
    for (auto x : adj[pos]) {
        if (cur_color[x] == cur_color[pos]) return 0;
    }
    return 1;
}

void sa() {
    double t_start = 100, t_final = 5;
    double t = t_start;
    std::uniform_real_distribution<> gen_rng(0, 1);
    int iter = 0;
    while (1) {
        if (timer.stopwatch() > TL) break;
        bool swap = 1;
        int pos1 = rng() % N;
        int pos2 = rng() % N;
        int new_color1 = cur_color[pos2];
        int new_color2 = cur_color[pos1];
        if (pos1 == pos2) continue;
        if (new_color1 == new_color2) continue;
        cur_color[pos1] = new_color1;
        cur_color[pos2] = new_color2;
        if (!ok(pos1) || !ok(pos2)) {
            cur_color[pos1] = new_color2;
            cur_color[pos2] = new_color1;
            continue;
        }
        iter++;
        if (iter & 63 == 0) t = t_start * pow(t_final / t_start, (double)timer.stopwatch() / TL);

        if (swap) {
            tot[new_color1] += w[pos1] - w[pos2];
            tot[new_color2] += w[pos2] - w[pos1];

        } else {
            tot[new_color1] += w[pos1];
            tot[new_color2] -= w[pos1];
        }

        ll mi = 1e18, ma = 0;
        for (auto x : tot) {
            mi = min(mi, x);
            ma = max(ma, x);
        }
        ll new_score = ma - mi;
        if (new_score < cur_score || gen_rng(rng) < exp((cur_score - new_score) / t)) {
            cur_score = new_score;
        } else {
            tot[new_color1] -= w[pos1] - w[pos2];
            tot[new_color2] -= w[pos2] - w[pos1];
            cur_color[pos1] = new_color2;
            cur_color[pos2] = new_color1;
        }

        if (cur_score < best) {
            best = cur_score;
            ans = cur_color;
        }
        if (iter % 1000000 == 0) cerr << iter << " " << best << endl;
    }
    cerr << "iter: " << iter << endl;
}
int main() {
    timer.begin();
    cin >> N >> K;
    adj.resize(N);
    w.resize(N);
    for (auto &x : w) cin >> x;

    for (auto &a : adj) {
        int l;
        cin >> l;
        a.resize(l);
        for (auto &x : a) cin >> x;
    }
    tot.resize(K, 0);
    ans = initial_sol();
    ans = fix_sol(ans);
    cur_color = ans;
    for (int i = 0; i < N; ++i) {
        tot[ans[i]] += w[i];
    }
    best = *max_element(tot.begin(), tot.end()) - *min_element(tot.begin(), tot.end());
    cur_score = best;
    cerr << cur_score << endl;
    sa();
    for (auto x : ans) cout << x << " ";
    cout << endl;
    cerr << best << endl;
}
