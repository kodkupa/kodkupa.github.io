// @check-accepted: *

#include <cassert>
#include <cmath>
#include <iostream>

int main() {
    double Dx, Dy, Ds;
    std::cin >> Dx >> Dy >> Ds;

    double Bx, By, Bs;
    std::cin >> Bx >> By >> Bs;

    char dir;
    std::cin >> dir;

    if (dir == 'U' || dir == 'D') {
        std::swap(Dx, Dy);
        std::swap(Bx, By);
        dir = (dir == 'U') ? 'R' : 'L';
    }
    if (dir == 'L') {
        Dx = -Dx;
        Bx = -Bx;
        dir = 'R';
    }

    double T1 = std::abs(Dy - By) / Ds;
    assert(T1 >= 0);
    Bx += Bs * T1;

    if (Bx > Dx && Ds <= Bs) {
        std::cout << -1 << '\n';
        return 0;
    }

    double T2 = (Bx > Dx) ? (Bx - Dx) / (Ds - Bs) : (Dx - Bx) / (Ds + Bs);
    assert(T2 >= 0);
    std::cout << (long long)std::ceil(T1 + T2) << '\n';
}
