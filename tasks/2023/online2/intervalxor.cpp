#include <utility>
#include <iostream>
#pragma GCC optimize("O3")
#define fi first
#define se second
#define pb push_back
#define pf push_front
 
// #define fisier 1 
 
using namespace std;
 
typedef long long ll;
 
const int mod = 1000000007;
const double PI = 3.14159265359; 
const double eps = 1e-9;

pair<int, int> f(int x)
{
	int ans = 0;
	for(int i = x-x%4; i <= x; i++)
		ans ^= i;
		
	int ans2 = ans;
	int max_bit = 0;
	
	while((1<<(1+max_bit)) <= x)
		max_bit++;
	
	int L = 0;
	int R = x;
	
	for(int i = max_bit; i >= 0; i--)
	{
		if((ans2 & (1<<i)) == 0 && L + (1<<i) <= R)
		{
			ans2 ^= (1<<i);
			L += (1<<i);
		}
	}
	
	return {ans, ans2};
}
int main()
{
	#ifdef fisier
		ifstream cin("input.in");
		ofstream cout("output.out");
	#endif
	
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int q;
	cin >> q;
	for(; q; --q)
	{
		int a;
		cin >> a;
		pair<int, int> sol = f(a);
		cout << sol.fi << " " << sol.se << '\n';
	}
	return 0;
}
