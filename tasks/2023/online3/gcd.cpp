// model solution
// @check-accepted: *

#include <iostream>

using namespace std;

int digits(long long n) {
    if (n < 10) return 1;
    return digits(n / 10) + 1;
}

int main() {
    long long n, d, a = 0, b = 0;
    cin >> n >> d;
    if (digits(2 * d) <= n) {
        // solution exists
        a = d;
        while (digits(a) < n) a *= 10;
        b = a + d;
        if (digits(b) != n) b = a - d;
    }
    cout << a << " " << b << endl;
    return 0;
}
