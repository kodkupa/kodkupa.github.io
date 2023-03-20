// @check-accepted: examples 2-digit NT<=1000 all
// insert brief description of the solution here

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
int N;
string S;
int dist(int a, int b, int swapa, int swapb, bool x) {
    if (x) {
        if (swapa == a)
            a = swapb;
        else if (a == swapb)
            a = swapa;
    }
    if (swapa == b)
        b = swapb;
    else if (b == swapb)
        b = swapa;

    return abs(b - a);
}
bool vis[100000][10][10];
int memo[100000][10][10];
int sol(int pos, int swapa = 0, int swapb = 0) {
    if (pos == N) return 0;
    if (vis[pos][swapa][swapb]) return memo[pos][swapa][swapb];
    vis[pos][swapa][swapb] = true;
    int tot = 0;
    // distance from previous
    if (pos)
        tot = dist(S[pos - 1] - '0', S[pos] - '0', swapa, swapb, 1);
    else
        tot = dist(0, S[pos] - '0', swapa, swapb, 1);

    int best = tot + sol(pos + 1, swapa, swapb);
    if (swapa == swapb) {
        // try all possible swaps before pressing current button
        for (int i = 0; i < 10; i++) {
            for (int j = i + 1; j < 10; j++) {
                if (pos)
                    best = min(best, dist(S[pos - 1] - '0', S[pos] - '0', i, j, 0) + sol(pos + 1, i, j));
                else
                    best = min(best, dist(0, S[pos] - '0', i, j, 0) + sol(pos + 1, i, j));
            }
        }
    }
    return memo[pos][swapa][swapb] = best;
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> S;
        N = S.size();
        for (int i = 0; i < N; i++)
            for (int j = 0; j < 10; j++)
                for (int k = 0; k < 10; k++) vis[i][j][k] = 0;
        cout << sol(0) << endl;
    }
}
