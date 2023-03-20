#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
 
#define fi first
#define se second
#define pb push_back
const int N = 100005, lvls = 20, Q = 100005, BlockSize = 500;
int n, q, Values[N], par[N][lvls], hgt[N], NodeOccurrence[N], DFSOrder[N+N], TimeIN[N], TimeOUT[N], Time, qIndex[Q], qL[Q], qR[Q], qLca[Q], qAns[Q], NumberOfDistinctValues[N/BlockSize+10], Frequency[N];
vector <int> v[N];
 
bool isnpr[1000006];
int prnum[1000006];
vector<int> prims;
 
void dfs(int x) {
	DFSOrder[TimeIN[x] = Time++] = x;
	for (int i = 1; i < lvls; i++) {
		par[x][i] = par[par[x][i-1]][i-1];
	}
	for (int y : v[x]) {
		if (y == par[x][0]) continue;
		par[y][0] = x;
		hgt[y] = hgt[x] + 1;
		dfs(y);
	}
	DFSOrder[TimeOUT[x] = Time++] = x;
}
 
int Kth(int x, int k) {
	for (int i = 0; (1 << i) <= k; i++) {
		if ((1 << i) & k) {
			x = par[x][i];
		}
	}
	return x;
}
 
int LCA(int x, int y) {
	if (hgt[x] < hgt[y]) {
		swap(x, y);
	}
	x = Kth(x, hgt[x] - hgt[y]);
	if (x == y) return x;
	for (int i = lvls - 1; i >= 0; i--) {
		if (par[x][i] != par[y][i]) {
			x = par[x][i];
			y = par[y][i];
		}
	}
	return par[x][0];
}
 
void add(int x) {
	if (x > n) return;
	if (Frequency[x]++ == 0) {
		NumberOfDistinctValues[x/BlockSize]++;
	}
}
 
void rem(int x) {
	if (x > n) return;
	if (--Frequency[x] == 0) {
		NumberOfDistinctValues[x/BlockSize]--;
	}
}
 
void change(int x) {
	if (NodeOccurrence[x] ^= 1) {
		add(Values[x]);
	} else {
		rem(Values[x]);
	}
}
 
int getAns() {
	int ret = 0;
	for (int i = 0; ret <= n; ret += BlockSize, i++) {
		if (NumberOfDistinctValues[i] != BlockSize) break;
	}
	while (Frequency[ret]) ret++;
	return ret;
}
 
void mo() {
	sort(qIndex, qIndex + q, [&](int a, int b) {
		return make_pair(qL[a] / BlockSize, qR[a]) < make_pair(qL[b] / BlockSize, qR[b]);
	});
	int l = 0, r = -1;
	for (int i = 0; i < q; i++) {
		int cur = qIndex[i];
		while (r < qR[cur]) change(DFSOrder[++r]);
		while (r > qR[cur]) change(DFSOrder[r--]);
		while (l > qL[cur]) change(DFSOrder[--l]);
		while (l < qL[cur]) change(DFSOrder[l++]);
		add(Values[qLca[cur]]);
		qAns[cur] = getAns();
		rem(Values[qLca[cur]]);
	}
	for (int i = 0; i < q; i++) {
		cout << prims[qAns[i]] << '\n';
	}
}
 
void init() {
	Time = 0;
	for (int i = 1; i <= n; i++) {
		Frequency[i] = NodeOccurrence[i] = 0;
		v[i].clear();
	}
	Frequency[0] = 0;
	int NumberOfBlocks = N / BlockSize + 10;
	for (int i = 0; i < NumberOfBlocks; i++) {
		NumberOfDistinctValues[i] = 0;
	}
}
 
 
 
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	memset(prnum, 0x7f, sizeof prnum);
	isnpr[0] = isnpr[1] = true;
	int hano = 0;
	for(int i=2;i<=1000003;i++){
		if(!isnpr[i]){
			prnum[i] = hano++;
			prims.push_back(i);
			for(int j=i+i;j<=1000003;j+=i){
				isnpr[j] = true;
			}
		}
	}
	
	cin >> n ;
	init();
	for (int i = 1; i <= n; i++) {
		cin >> Values[i];
		Values[i] = prnum[Values[i]];
	}
	for (int i = 1; i < n; i++) {
		int x, y;
		cin >> x >> y;
		v[x].pb(y);
		v[y].pb(x);
	}
	dfs(1);
	cin>>q;
	for (int i = 0; i < q; i++) {
		int x, y;
		cin >> x >> y;
		qIndex[i] = i;
		qLca[i] = LCA(x, y);
		if (qLca[i] == x || qLca[i] == y) {
			qL[i] = TimeIN[x];
			qR[i] = TimeIN[y];
		} else {
			if (TimeIN[x] < TimeIN[y]) {
				qL[i] = TimeOUT[x];
				qR[i] = TimeIN[y];
			} else {
				qL[i] = TimeOUT[y];
				qR[i] = TimeIN[x];
			}
		}
		if (qL[i] > qR[i]) {
			swap(qL[i], qR[i]);
		}
	}
	mo();
	return 0;
}
