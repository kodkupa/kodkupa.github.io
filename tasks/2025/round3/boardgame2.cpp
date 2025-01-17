#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll INF = 1e18;

vector<ll> top;
vector<bool> vis, leave;
vector<vector<pair<ll, ll> > > g;

bool ok;

void dfs(ll x) {
	vis[x] = 1;
	for(pair<ll, ll> sz : g[x]) {
		if(!vis[sz.first]) dfs(sz.first);
		else if(!leave[sz.first]) ok = 0;
	}

	leave[x] = 1;
	top.push_back(x);
}

int main() {
	ll n,m;
	cin >> n >> m;

	vis.assign(n+1, 0);
	leave.assign(n+1, 0);
	g.resize(n+1);
	ok = 1;
	for(ll i = 0; i < m; i++) {
		ll x,y,z;
		cin >> x >> y >> z;

		g[x].push_back({y, z});
	}

	for(ll i = 0; i < n; i++) {
		if(!vis[i+1]) dfs(i+1);
	}

	vector<ll> winning(n+1, 0);
	for(ll i = 0; i < n; i++) {
		for(pair<ll, ll> sz : g[top[i]]) {
			if(!winning[sz.first]) winning[top[i]] = 1;
		}
	}


	vector<ll> dp(n+1, 0);
	for(ll i = 0; i < n; i++) {
		ll x = top[i];
		if(winning[x] && !g[x].empty()) dp[x] = INF;
		else dp[x] = 0;
		for(pair<ll, ll> sz : g[x]) {
			if(winning[x]) {
				if(!winning[sz.first]) {
					dp[x] = min(dp[x], sz.second + dp[sz.first]);
				}
			}
			else {
				dp[x] = max(dp[x], dp[sz.first]);
			}
		}
	}

	if(winning[1]) cout << "Alice\n";
	else cout << "Bob\n";
	cout << dp[1] << "\n";
}
