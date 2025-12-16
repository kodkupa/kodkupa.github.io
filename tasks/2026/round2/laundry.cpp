// insert brief description of the solution here
// @check-accepted: *

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  int N, C, W;
  cin >> N >> C >> W;
 
  vector<int> T(N);
  for (int i = 0; i < N; ++i) cin >> T[i];

  sort(T.rbegin(), T.rend());
  
  long long ans = W;
  
  for (int i = 0; i + C < N; i += C) {
    ans += max<long long>(W, T[i]);
  }
  
  ans += T[N-1 - ((N-1) % C)];
  
  cout << ans << "\n";
  return 0;
}
