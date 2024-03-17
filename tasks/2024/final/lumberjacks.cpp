// @check-accepted: examples QNsquare SmallV QNlogN QN N+QlogN
#include <fstream>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin>>n>>q;

    vector<int> v(n);
    for(int &x : v) cin>>x;

    set<int> pos;
    
    auto check = [&v, n](int i) -> bool {
        int prv = i == 0 ? n-1 : i-1;
        return v[prv] >= v[i];
    };

    auto dist = [n](int l, int r) -> int {
        if(l == r) return n;
        if(r < l) return r - l + n;
        return r - l;
    };

    int odd = 0;
    auto add = [&pos, &odd, n, dist](int x) -> void {
        if(pos.empty()){
            pos.insert(x);
            odd = n % 2;
        } else{
            auto it = pos.insert(x).first;
            auto prv = it != pos.begin() ? prev(it) : prev(pos.end());
            auto nxt = next(it) != pos.end() ? next(it) : pos.begin();
            odd -= dist(*prv, *nxt) % 2;
            odd += dist(*it,  *nxt) % 2;
            odd += dist(*prv, *it) % 2;
        }
    };

    auto rem = [&pos, &odd, n, dist](int x) -> void {
        if(pos.size() == 1){
            odd = 0;
            pos.clear();
        } else{
            auto it = pos.find(x);
            auto prv = it != pos.begin() ? prev(it) : prev(pos.end());
            auto nxt = next(it) != pos.end() ? next(it) : pos.begin();
            odd += dist(*prv, *nxt) % 2;
            odd -= dist(*it,  *nxt) % 2;
            odd -= dist(*prv, *it) % 2; 
            pos.erase(x);
        }
    };

    for(int i = 0; i < n; i++){
        if(check(i)) add(i);
    }

    cout << (n - odd) / 2 << ' ';

    while(q--){
        int x, c;
        cin>>x>>c;

        if(check(x)) rem(x);
        if(check((x+1)%n)) rem((x+1)%n);

        v[x] = c;

        if(check(x)) add(x);
        if(check((x+1)%n)) add((x+1)%n);

        cout << (n - odd) / 2 << ' ';
    }

    cout << '\n';

    return 0;
}
