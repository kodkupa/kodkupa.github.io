// @check-accepted: examples NDsmall Nsmall Dsmall no-limits
#include <iostream>
#include <vector>
using namespace std;

int main() {

  int N, D;
  cin >> N >> D;
   
  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  vector<int> B(N);
  for (int i = 0; i < N; i++) {
    cin >> B[i];
  }

  bool ok = true;
  for (int i = 0; i < N; i++) {
    if (B[i]-D > A[i]) {
      ok = false;
      break;
    }
  }

  if (ok) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }

  return 0;
}
