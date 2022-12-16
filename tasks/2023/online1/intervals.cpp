#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
int N;
vector<pair<int, int> > v;
int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        v.push_back({a, b});
    }
    sort(v.begin(), v.end(), [](pair<int, int> a, pair<int, int> b) {
        if (a.second == b.second) return a.first < b.first;
        return a.second < b.second;
    });
    map<int, int> k;
    int tot = N;
    for (int i = 0; i < N; i++) {
        if (k[v[i].first] > 0) {
            k[v[i].first]--;
            tot--;
        }
        k[v[i].second]++;
    }
    cout << tot << endl;
}
