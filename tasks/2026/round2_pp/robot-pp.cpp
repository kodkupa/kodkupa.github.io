// @check-accepted: examples NMsmall RD no-limits

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    string P;
    cin >> P;
    int free_cells = N * M - 1;
    vector<vector<bool> > vis(N, vector<bool>(M, false));
    vis[0][0] = true;
    int x = 0, y = 0;
    for (int i = 0; i < P.size(); i++) {
        auto c = P[i];
        if (c == 'R') {
            y++;
        } else if (c == 'L') {
            y--;
        } else if (c == 'U') {
            x--;
        } else if (c == 'D') {
            x++;
        }
        if (!vis[x][y]) {
            vis[x][y] = true;
            free_cells--;
        }
        if (free_cells == K - 1) {
            cout << i << endl;
            return 0;
        }
    }
    cout << P.size() << endl;
}
