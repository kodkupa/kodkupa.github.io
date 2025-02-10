// @check-accepted: *
// brute force O(NlogN)

#include <iostream>
#include <vector>
using namespace std;

void countDigits(int N) {
  // Initialize a vector to count occurrences of each digit (0-9)
  vector<int> digitCount(10, 0);
    
  // Iterate through all numbers from 1 to N
  for (int i = 1; i <= N; ++i) {
    int num = i;
    // Count each digit in the current number
    while (num > 0) {
      digitCount[num % 10]++;
      num /= 10;
    }
  }

  // Output the result
  for (int i = 0; i < 10; ++i) {
    cout << digitCount[i] << " ";
  }
  cout << '\n';
}

int main() {
  // Input: length of the race
  int N;
  cin >> N;
  
  // Call the function to count digits
  countDigits(N);

  return 0;
}
