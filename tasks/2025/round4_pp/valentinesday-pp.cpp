// @check-accepted: *

#include <iostream>
#include <vector>

using namespace std;

int main() {
  int N, M;
  cin >> N >> M;

  vector<int> C(N);
  for (int i = 0; i < N; ++i) {
    cin >> C[i];
  }
  
  vector<int> P(N);
  for (int i = 0; i < N; ++i) {
    cin >> P[i];
  }
  
  int maxChocolates = 0;
  
  for (int i = 0; i < N; ++i) {
    if (C[i] % 2 == 0 && P[i] <= M && C[i] > maxChocolates) {
      maxChocolates = C[i];
    }
  }
  
  cout << maxChocolates << endl;
  
  return 0;
}
