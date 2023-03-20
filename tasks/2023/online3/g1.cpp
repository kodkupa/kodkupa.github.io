// @check-accepted: examples NVsmall no-limits
#include <iostream>
#include <cassert>
using namespace std;

int player[200005];
int p[200005];
int cnt[200005];
int n, q;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
    {
        cin >> player[i];
        p[player[i]] = i;
    }

    int mx = 0;
    int ans = -1;

    while (q--)
    {
        int playerAct;
        cin >> playerAct;

        int pos = p[playerAct];
        
        assert(pos != 1);

        swap(player[pos], player[pos - 1]);

        p[player[pos]] = pos;
        p[player[pos - 1]] = pos - 1;
        cnt[player[pos]]++;

        if (cnt[player[pos]] == mx)
        {
            ans = min(player[pos], ans);
        }

        if (cnt[player[pos]] > mx)
        {
            ans = player[pos];
            mx = cnt[player[pos]];
        }
        cout << ans << '\n';
        
    }
}

