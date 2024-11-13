// @check-accepted: examples NQsmall Qsmall Bsmall full
#include <bits/stdc++.h>
using namespace std;

const int B = 20;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin>>n>>q;

    vector<int> v(n), masks(1<<B);
    for(int i = 0; i < n; i++){
        cin>>v[i];
        masks[v[i]] = v[i];
    }

    for(int i = (1<<B) - 1; i > 0; i--){
        int b = __builtin_ctz(i);
        masks[i^(1<<b)] |= masks[i];
        masks[(1<<b)] |= masks[i];
    }
    masks[0] = 0;
    for(int i = 1; i < (1<<B); i++){
        int b = __builtin_ctz(i);
        masks[i] |= masks[i^(1<<b)];
        masks[i] |= masks[(1<<b)];
    }

    for(int i = 0; i < q; i++){
        int x, y;
        cin>>x>>y;
        x = v[x - 1];
        y = v[y - 1];
        int ans = 1;
        while((x&y) == 0 && masks[x] != x){
            x = masks[x];
            ans++;
        }

        cout << ((x&y) == 0 ? -1 : ans) << '\n';
    }

    return 0;
}
