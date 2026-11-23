// O(N α(N)) BFS over dry tiles: landing tiles are precomputed, and a DSU "next unscanned tile" pointer scans every jump target only once.

#include <algorithm>
#include <climits>
#include <cstdio>
#include <deque>
#include <numeric>
#include <vector>
using namespace std;

vector<int> nxt;
int findNext(int x) {
    while (nxt[x] != x) {
        nxt[x] = nxt[nxt[x]];
        x = nxt[x];
    }
    return x;
}

int main() {
    int n;
    scanf("%d", &n);
    vector<int> B(n), S(n), land(n);
    for (int i = 0; i < n; i++) scanf("%d", &B[i]);
    for (int i = 0; i < n; i++) scanf("%d", &S[i]);
    for (int k = n - 1; k >= 0; k--) land[k] = (S[k] != -1) ? land[S[k]] : k;

    nxt.resize(n + 1);
    iota(nxt.begin(), nxt.end(), 0);

    vector<int> dist(n, -1);
    vector<int> q = {0};
    dist[0] = 0;
    for (size_t h = 0; h < q.size(); h++) {
        int u = q[h];
        int hi = u + B[u];
        for (int j = findNext(u + 1); j <= hi; j = findNext(j)) {
            nxt[j] = j + 1;  // j is used up
            int v = land[j];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push_back(v);
            }
        }
    }
    printf("%d\n", dist[n - 1]);
}
