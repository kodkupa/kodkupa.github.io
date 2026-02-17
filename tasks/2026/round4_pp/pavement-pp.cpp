// @check-accepted: examples S1 H1 small full
#include <iostream>
using namespace std;

int H, W, S;

int f(int X, int Y) {
    //both smaller than half tile
    if (2 * W <= S) 
        return (X + Y + 1) / 2;
    
    // both greater than half tile
    if (H > S / 2)
        return X + Y;

    // the sum doesn't fit on a tile
    if (H + W > S) 
        return Y + (X + 1) / 2;
    
    if (X < Y) 
        return Y;

    return Y + (X - Y + 1) / 2;
}

int main() {
    cin >> H >> W >> S;

    int X = W / S; // how many horizontally
    int Y = H / S; // how many vertically

    int T = X * Y;
    H %= S; W %= S;

    //assume H <= W
    if (H > W) {
        swap(H, W);
        swap(X, Y);
    }

    // X of size S*H
    // Y of size S*W
    // 1 of size H*W

    if (H == 0) {
        if (W) {
            T += f(0, Y);
        }
    } else {
        T += min(f(X + 1, Y), f(X, Y + 1));
    }
    // try both considering the corner in one of the two

    cout << T << endl;

    return 0;
}
