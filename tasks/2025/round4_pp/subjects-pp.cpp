#include <fstream>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    int n,m;
    cin >> n >> m;

    vector<vector<bool> > subjects(m+1, vector<bool>(m+1, 0));

    for(int i = 0; i < n; i++) {
        int k;
        cin >> k;

        vector<int> temp(k);
        for(int &j : temp) cin >> j;

        for(int j = 0; j < k; j++) {
            for(int l = j+1; l < k ; l++) {
                subjects[temp[j]][temp[l]] = 1;
                subjects[temp[l]][temp[j]] = 1;
            }
        }
    }
    vector<pair<int, int> > ki;
    for(int i = 1; i <= m; i++) {
        for(int j = i+1; j <= m; j++) {
            if(!subjects[i][j]) {
                ki.push_back({i, j});
            }
        }
    }
    cout << ki.size() << "\n";
    for(pair<int, int> i : ki) cout << i.first << " " << i.second << "\n";
    
    return 0;
}
