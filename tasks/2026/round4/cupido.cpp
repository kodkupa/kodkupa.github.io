#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int main() {
    int N;
    cin >> N;
    unordered_map<int, unordered_set<int>> likes;

    for (int i = 0; i < N; ++i) {
        int id, a, b, c;
        cin >> id >> a >> b >> c;
        likes[id].insert(a);
        likes[id].insert(b);
        likes[id].insert(c);
    }

    int mutual = 0;
    for (const auto& pair : likes) {
        int id = pair.first;
        const unordered_set<int>& liked = pair.second;
        for (int l : liked) {
            if (likes.count(l) && likes[l].count(id)) {
                mutual++;
            }
        }
    }

    cout << mutual / 2 << endl;
    return 0;
}