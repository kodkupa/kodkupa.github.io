// Full solution: turn each roll into a score that can be compared directly.
// A double d-d gets 100 + d (more than any non-double, which is at most 56),
// any other roll gets 10 * smaller + larger.

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int score(int x, int y) {
    if (x == y)
        return 100 + x;
    return 10 * min(x, y) + max(x, y);
}

int main() {
    int N;
    cin >> N;

    int W1 = 0, W2 = 0, X = 0;
    for (int i = 0; i < N; i++) {
        int A, B, C, D;
        cin >> A >> B >> C >> D;
        int s1 = score(A, B), s2 = score(C, D);
        if (s1 > s2)
            W1++;
        else if (s2 > s1)
            W2++;
        else
            X++;
    }

    cout << W1 << " " << W2 << " " << X << endl; // print the result
    return 0;
}
