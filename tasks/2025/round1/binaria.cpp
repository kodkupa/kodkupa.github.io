// @check-accepted: examples NTtiny fit-int no-limits
// insert brief description of the solution here

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  // uncomment the following lines if you want to read/write from files
  // ifstream cin("input.txt");
  // ofstream cout("output.txt");

  int N;
  cin >> N;
  long books = 0;

  for (int i = 0; i < N; i++) {
    long T;
    cin >> T;
    long power = 1;
    while (power < T) {
      power = 2 * power + 1;
    }
    books += power - T;
  }

  // insert your code here

  cout << books << endl; // print the result
  return 0;
}
