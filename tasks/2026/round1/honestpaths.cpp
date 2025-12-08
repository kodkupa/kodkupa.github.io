// @check-accepted: examples Nsmall GraphSmall Tree UnitWeights no-limits
#include <vector>
#include <array>
#include <queue>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
using namespace std;
typedef long long ll;
#define pb push_back
#define all(x) x.begin(), x.end()
typedef array<ll, 2> ll2;
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m, trg;
  cin >> n >> m;
  trg = n;
  vector<vector<ll2>> vec(n + 1);
  vector<ll> dist(n + 1, (ll)1e15);
  dist[trg] = 0;
  vector<ll> dp(n + 1);
  vector<ll> nxt(n + 1);

  for (int i = 1; i <= m; i++){
    ll x, y, w;
    cin >> x >> y >> w;
    vec[x].pb({w, y});
    vec[y].pb({w, x});
  }
  priority_queue<ll2, vector<ll2>, greater<ll2>> pq;
  pq.push({0, trg});
  while (!pq.empty()){
    auto [cur, nod] = pq.top();
    pq.pop();
    if (dist[nod] != cur) continue;
    for (auto [w, y] : vec[nod]){
      if (w + cur < dist[y]){
        dist[y] = cur + w;
        pq.push({dist[y], y});
      }
    }
  }

  vector<int> ord(n);
  dp[trg] = 0;
  iota(all(ord), 1);
  sort(all(ord), [&] (ll a, ll b){
    return dist[a] < dist[b];
  });
  ll rez = trg;
  for (auto x : ord){
    for (auto [w, y] : vec[x]){
      if (dist[y] >= dist[x]) continue;
      if (dp[y] + w > dp[x]){
        dp[x] = dp[y] + w;
        nxt[x] = y;
      }
    }
    if (dp[x] > dp[rez]){
      rez = x;
    }
  }
  vector<int> ans;
  int x = rez;
  do{
    ans.pb(x);
    x = nxt[x];
  } while (x != 0);
  cout << dp[rez] << ' ';
  cout << ans.size() << '\n';
  for (auto x : ans) cout << x << ' ';
  cout << '\n';
  return 0;
}
