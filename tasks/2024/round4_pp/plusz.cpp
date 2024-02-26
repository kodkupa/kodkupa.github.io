// @check-accepted: examples small no-limits
// insert brief description of the solution here

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {

  int V,A,B,F,C,D;
  cin >> V >> A >> B;
  cin >> F >> C >> D;

  if (A+B==2*F and C+D==2*V) {
    if (B-A==D-C) {
      cout << "IGEN" << endl;
    } else {
      cout << "NEM" << endl;
    }
  } else {
    cout << "NEM" << endl;
  }
    
  return 0;
}
