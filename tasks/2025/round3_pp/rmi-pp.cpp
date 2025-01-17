// @check-accepted: *

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int A, B, N;
  cin >> A >> B >> N;
    
  vector<int> F(N);
  for (int i = 0; i < N; i++) {
    cin >> F[i];
  }

  vector<int> S(N);
  for (int i = 0; i < N; i++) {
    cin >> S[i];
  }
  
  sort(F.begin(), F.end());
  sort(S.begin(), S.end());
  
  int best = 1, worst = 1, summa = A + B, i, j;
  i = N - 1;
  j = 0;

  while (i >= 0) {
    if (F[i] + S[j] > summa) {
      best += 1;
      i -= 1;
    }
    else {
      i -= 1;
      j += 1;
    }
  }

  i = N - 1;
  j = 0;
  while (j < N) {
    if (F[i] + S[j] > summa) {
      worst += 1;
      i -= 1;
      j += 1;
    }
    else {
      j += 1;
    }
  }

  cout << best << ' ' << worst << endl; // print the result
  return 0;
}
