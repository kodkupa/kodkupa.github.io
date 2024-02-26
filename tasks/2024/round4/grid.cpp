// insert brief description of the solution here

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int main() {
    int N, M, R, G, B;
    cin >> N >> M >> R >> G >> B;

    vector<string> ans(N, string(M, ' '));
    vector<pair<int, char>> col = {{R, 'R'}, {G, 'G'}, {B, 'B'}};

    sort(col.rbegin(), col.rend());

    if(col[0].first > (N*M + 1)/2){
        cout << "NO" << endl;
        return 0;
    }else{
        cout << "YES" << endl;
    }

    vector<pair<int, int>> pts;
    pts.reserve(N*M);
    for(int i = 0; i < N; ++i)for(int j = 0; j < M; ++j)pts.push_back({i,j});
    stable_sort(pts.begin(), pts.end(), [&](auto a, auto b)->bool{
        if(N > M)return a.first < b.first;
        else return a.second < b.second;
    });

    for(auto [i,j]: pts){
        if((i + j) % 2 == 0){
            if(--col[0].first >= 0)ans[i][j] = col[0].second;
            else{
                ans[i][j] = col[2].second;
                --col[2].first;
            }
        }
    }
    for(auto [i,j]: pts){
        if((i + j) % 2){
            if(--col[2].first >= 0)ans[i][j] = col[2].second;
            else{
                ans[i][j] = col[1].second;
            }
        }
    }

    for(auto s: ans)cout << s << endl;

    return 0;
}
