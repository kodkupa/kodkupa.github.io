// Bevasarlas megoldas

// Moho elv alapjan erdemes valasztani a gyumolcsleveket, eloszor megveszunk a
// legolcsobbol annyit amennyit csak tudunk, aztan a masodik legolcsobbol es
// vegul a harmadikbol.

#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    // Ha nincs osszesen 10 doboz, akkor a megoldas -1.
    if (a + b + c < 10) cout << -1 << '\n';
    // Ha van legalabb 10 almale, akkor csak azt veszunk.
    else if (a >= 10) cout << 10 * 300 << '\n';
    // Egyebkent megvesszuk az osszes almalevet, es ha baracklevel egyutt megvan
    // a 10 doboz, akkor azokkal egeszitjuk ki.
    else if (a + b >= 10) cout << a * 300 + (10 - a) * 350 << '\n';
    // Ha nem eleg az alma + barack, akkor mindet megvesszuk es a maradekot
    // pedig cseresznyebol, amennyi kell a 10 dobozhoz.
    else cout << a * 300 + b * 350 + (10 - a - b) * 400 << '\n';
    return 0;
}