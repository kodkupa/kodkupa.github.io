// @check-accepted: examples N=0 no-limits

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int M, N, K;

    cin >> M >> N >> K;

    if ( (N+M)%K == 0 ) {
        cout << "IGEN" << endl;
    } else {
        cout << "NEM" << endl;
      }

    return 0;
}
