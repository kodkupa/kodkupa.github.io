// @check-accepted: examples small_h medium_h_one_wall medium_h_two_walls medium_h one_wall two_walls no-limits
// insert brief description of the solution here

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

struct Wall {
    int x;
    int y1, y2;
};

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);


    int T;
    cin >> T;
    for (; T > 0; T--) {
        int n, h, w;
        cin >> n >> h >> w;
        vector<Wall> walls(w + 1);
        walls[w].x = 2'000'000'000;
        for (int i = 0; i < w; i++) {
            cin >> walls[i].x;
        }
        for (int i = 0; i < w; i++) {
            cin >> walls[i].y1;
        }
        for (int i = 0; i < w; i++) {
            cin >> walls[i].y2;
        }

        sort(walls.begin(), walls.end(), [](Wall a, Wall b){return a.x < b.x;});
        int wi = 0;

        vector<vector<int>> min_angle(n, vector<int>(h, 2'000'000'000));
        vector<vector<int>> max_angle(n, vector<int>(h, -2'000'000'000));

        int sy = h / 2;
        min_angle[0][sy] = max_angle[0][sy] = 0;

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < h; j++) {
                if (i == walls[wi].x) {
                    if (j < walls[wi].y1 || j > walls[wi].y2) continue;                
                }
                for (int k = min_angle[i][j] - 1; k <= max_angle[i][j] + 1; k++) {
                    int ny = j + k;
                    if (ny < 0) continue;
                    if (ny >= h) continue;
                    
                    int nx = i + 1;
                    min_angle[nx][ny] = min(min_angle[nx][ny], k);
                    max_angle[nx][ny] = max(max_angle[nx][ny], k);
                }            
            }
            if (i == walls[wi].x) {
                wi++;        
            }
        }

        bool possible = false;
        for (int j = 0; j < h; j++) {
            if (min_angle[n - 1][j] <= max_angle[n - 1][j]) {
                possible = true;        
            }    
        }
        if (possible) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }

    return 0;
}
