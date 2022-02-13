// Bevasarlas megoldas

// Mohó elv alapjan érdemes valasztani a gyümölcsleveket, először megveszünk a
// legolcsóbból annyit amennyit csak tudunk, aztan a masodik legolcsóbból és
// végül a harmadikból.

#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    // Ha nincs összesen 10 doboz, akkor a megoldas -1.
    if (a + b + c < 10) cout << -1 << '\n';
    // Ha van legalabb 10 almalé, akkor csak azt veszünk.
    else if (a >= 10) cout << 10 * 300 << '\n';
    // Egyébként megvesszük az összes almalevet, és ha baracklével együtt megvan
    // a 10 doboz, akkor azokkal egészítjük ki.
    else if (a + b >= 10) cout << a * 300 + (10 - a) * 350 << '\n';
    // Ha nem elég az alma + barack, akkor mindet megvesszük és a maradékot
    // pedig cseresznyéből, amennyi kell a 10 dobozhoz.
    else cout << a * 300 + b * 350 + (10 - a - b) * 400 << '\n';
    return 0;
}