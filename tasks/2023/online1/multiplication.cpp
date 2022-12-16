// The solution is brute force, we generate the multiples of K until each digit occurs.
// To check the digits of a number, we repeat taking the remainder by 10 (last digit),
// and dividing the number by 10 (deleting last digit).
// We keep track which digit occurred in a bool vector.
// It is easy to prove that there cannot be more than 100 multiples until every digit occurs.
// In fact, the maximum we found is 72 for 125.

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int solve(int k) {
    vector<bool> digits(10);
    int cnt = 0, ans = 0;
    while (cnt < 10) {
        ans++;
        int x = ans * k;
        while (x > 0) {
            if (!digits[x % 10]) {
                cnt++;
                digits[x % 10] = true;
            }
            x /= 10;
        }
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        cout << solve(k) << '\n';
    }
    return 0;
}
