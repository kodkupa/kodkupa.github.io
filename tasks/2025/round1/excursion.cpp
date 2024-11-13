// @check-accepted: examples Nsmall no-limits

#include <iostream>
using namespace std;

int main() {
  int N, K, S;
  cin >> N >> K >> S;

  if (N * K < S) { cout << "NO" << endl; }
  else { cout << "YES" << endl; }
    
  return 0;
}
