// To determine the winner, we need to compare the sums of the two lists.
// To find the owner of the fastest lap, we need to compare the minimums of the two lists.

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <cassert>

using namespace std;

int main() {
    int n;
    cin >> n;
    int sumh = 0, sumv = 0, minh = INT_MAX, minv = INT_MAX, x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        sumh += x;
        minh = min(minh, x);
    }
    for (int i = 0; i < n; i++) {
        cin >> x;
        sumv += x;
        minv = min(minv, x);
    }
    assert(sumh != sumv && minh != minv);
    cout << (sumh < sumv ? "Hamilton\n" : "Verstappen\n");
    cout << (minh < minv ? "Hamilton\n" : "Verstappen\n");
    return 0;
}
