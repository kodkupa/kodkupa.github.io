#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t;
	cin>>t;
	
	int n;
	cin>>n;
	vector<pair<int,int> > v;
	for(int i=0;i<n;i++){
		int x,y;
		cin>>x>>y;
		v.push_back({x,1});
		v.push_back({y,3});
	}
	int m;
	cin>>m;
	
	for(int i=0;i<m;i++){
		int x,y;
		cin>>x>>y;
		v.push_back({x,2});
		v.push_back({y,4});
	}
	sort(v.begin(),v.end());
	int ans = 0;
	bool f = false,s = false;
	int lf = 0, ls = 0;
	for(int i=0;i<n+m+n+m;i++){
		if(v[i].second == 1){
			f = true;
			lf = v[i].first;
		}
		if(v[i].second == 2){
			s = true;
			ls = v[i].first;
			if(lf + t < ls){
				f = false;
			}
		}
		if(v[i].second == 3){
			if(!f)continue;
			f = false;
			if(s){
				ans += v[i].first - max(lf,ls) + 1;
			}
		}
		if(v[i].second == 4){
			s = false;
			if(f){
				ans += v[i].first - max(lf,ls) + 1;
				lf = v[i].first + 1;
			}
		}
	}
	
	cout<<ans<<endl;
	
	return 0;
}
