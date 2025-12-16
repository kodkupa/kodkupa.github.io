// @check-accepted: *
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
  int A, B;
  cin >> A >> B;
    
  cout << min((A + B) / 4, min(A, B)) << "\n";
  return 0;
}
