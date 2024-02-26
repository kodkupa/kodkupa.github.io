// @check-accepted: examples Nsmall Nmid no-limits
// insert brief description of the solution here

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  // uncomment the following lines if you want to read/write from files
  // ifstream cin("input.txt");
  // ofstream cout("output.txt");

  int N, tmp, res;
  cin >> N;
    
  res=1000000;
  
  for (int i = 0; i < N; i++) {
    cin >> tmp;
    if (tmp<res) {
      res=tmp;
    }
  }

  // insert your code here

  cout << res << endl; // print the result
  return 0;
}
