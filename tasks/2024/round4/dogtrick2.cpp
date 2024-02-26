#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;

const int N_MAX = 250000;

int N, M, K;
int T[N_MAX + 5];
vector <int> G[N_MAX + 5];
vector <int> Gt[N_MAX + 5];
bool vis[N_MAX + 5];
stack <int> S;
int ctc[N_MAX + 5];
int ctc_size[N_MAX + 5];
vector <int> Gr[N_MAX + 5];

void DFS(int node) {
    vis[node] = true;
    for(auto it : G[node]) {
        if(!vis[it]) {
            DFS(it);
        }
    }
    S.push(node);
}

void DFS_ctc(int node, int idx) {
    ctc[node] = idx;
    ctc_size[idx]++;
    for(auto it : Gt[node]) {
        if(ctc[it] == 0) {
            DFS_ctc(it, idx);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> K >> N;
    for(int i = 1; i <= K; i++) {
        cin >> T[i];
    }
    cin >> M;
    while(M--) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        Gt[y].push_back(x);
    }

    for(int i = 1; i <= N; i++) {
        sort(G[i].begin(), G[i].end());
    }

    for(int i = 1; i <= N; i++) {
        if(!vis[i]) {
            DFS(i);
        }
    }

    int L = 0;
    while(!S.empty()) {
        if(ctc[S.top()] == 0) {
            DFS_ctc(S.top(), ++L);
        }
        S.pop();
    }

    for(int i = 1; i <= N; i++) {
        for(auto it : G[i]) {
            Gr[ctc[i]].push_back(ctc[it]);
        }
    }

    for(int i = 1; i <= L; i++) {
        sort(Gr[i].begin(), Gr[i].end());
        Gr[i].resize(unique(Gr[i].begin(), Gr[i].end()) - Gr[i].begin());
    }

    int score = 2;
    memset(vis, false, sizeof(vis));
    for(int i = 1; i < K; i++) {
        auto find_neigh = [&](int x, int y) -> bool {
            return binary_search(G[x].begin(), G[x].end(), y);
        };

        auto reachable = [&](int a, int b) -> bool {
            if(a == b) {
                return true;
            }
            if(b < a) {
                return false;
            }
            queue<int> Q;
            Q.push(a);
            while(!Q.empty()) {
                int node = Q.front();
                Q.pop();
                if(node == b) {
                    return true;
                }
                for(auto it : Gr[node]) {
                    if(!vis[it] && it <= b) {
                        vis[it] = true;
                        Q.push(it);
                    }
                }
            }
            return false;
        };
        
        if(find_neigh(T[i], T[i + 1])) {
            score += 2;
        }
        else {
            int a = ctc[T[i]];
            int b = ctc[T[i + 1]];
            
            if(reachable(a, b)) {
                score += 1;
            }
            else {
                cout << score << "\n";
                return 0;
            }
        }
    }
    cout << score << "\n";
    return 0;
}