// Snow White rides down once, together with as many dwarfs as fit next to her.
// The remaining dwarfs go down in groups of W / D. If k rides go down,
// the elevator also has to come back up empty k - 1 times: 2k - 1 rides.

#include <algorithm>
#include <iostream>

using namespace std;

int main() {

    int W, S, D;
    cin >> W >> S >> D;

    int with_sw = min((W - S) / D, 7);    // dwarfs riding with Snow White
    int per_ride = W / D;                 // dwarfs in a ride without her
    int rest = 7 - with_sw;
    int down = 1 + (rest + per_ride - 1) / per_ride;

    cout << 2 * down - 1 << endl; // print the result
    return 0;
}
