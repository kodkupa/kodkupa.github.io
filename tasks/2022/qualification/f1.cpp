/*
Egy auto mozgasat egy masodfoku egyenlet irja le, ezert ket auto egymashoz
viszonyitott helyzete legfeljebb ketszer valtozik. Vegig lehet menni mind az n^2
paron es megnezni, hogy mikor cserel helyet az i. es j. auto Az indulasi sorrend
ismert. Ezutan sorban fel kell dolgozni a q kerdest, es maximum n^2 elozest.
Mindig tudni kell az aktualis sorrendet. Igy a kerdesekre konnyu valaszolni, es
az elozeseknel is csak ki kell cserelni a ket auto helyet. Komplexitas:
O(n^2+q)*log(n^2+q)

Technikai reszlet: amikor ket auto egy pillanatban azonos helyen van, akkor a
kisebb indexu van elorebb. Ez okozhat nehezsegeket. Erdemes miden auto
konstansahoz egy kis erteket hozzaadni (a kisebb indexuekhez tobbet), ugy hogy
ne legyenek elozesek egesz ertekeken.
*/

#include <bits/stdc++.h>

using namespace std;

const int max_n = 2005;
int n, q, valasz[200005], sorrend[max_n], hely[max_n];
// sorrend[i] - az i. helyen allo auto
// hely[i] - hanyadik helyen all az i. auto
long double a[max_n], b[max_n], c[max_n], eps = 1e-9;

vector<pair<pair<long double, bool>, pair<int, int> > > e;

void pb(long double a, bool b, int c, int d) {
  // b==0 eseten a c auto megelozi a d-t
  // b==1 eseten a c. helyen levo auto a d. kerdes
  e.push_back({{a, b}, {c, d}});
}

int main() {
  ios_base::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> b[i] >> c[i];
    c[i] += (n - i) * eps;  // igy azonos erteknel a kisebb indexu van elol
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (c[i] >= c[j]) continue;

      // alapbol a j. auto van elol
      long double aa = a[i] - a[j], bb = b[i] - b[j], cc = c[i] - c[j];
      // ahol aax^2+bbx+cc=0, es x>0 ott a ket auto helyet cserel

      if (abs(aa) < eps) {
        if (abs(bb) < eps)
          continue;
        else {
          long double csere = -cc / bb;  // elsofolu egyenlet megoldasa
          if (csere > 0) {
            pb(csere, 0, i, j);
          }
        }
      } else {
        long double s = bb * bb - 4 * aa * cc;  // masodfuku egyenlet megoldasa
        if (s < 0) continue;
        long double x1 = (-bb - sqrt(s)) / (2 * aa),
                    x2 = (-bb + sqrt(s)) / (2 * aa);
        if (x1 > x2) swap(x1, x2);

        // harom lehetoseg van, attol fuggoen, hogy melyik megoldas negativ
        if (x2 < 0)
          continue;
        else if (x1 < 0) {
          pb(x2, 0, i, j);
        } else {
          pb(x1, 0, i, j);
          pb(x2, 0, j, i);
        }
      }
    }
  }

  cin >> q;
  for (int i = 1; i <= q; i++) {
    long double a;
    int c;
    cin >> a >> c;
    pb(c, 1, a, i);
  }

  // az alap sorrend
  for (int i = 1; i <= n; i++) {
    sorrend[i] = i;
    hely[i] = i;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (c[sorrend[j]] > c[sorrend[i]]) {
        swap(sorrend[i], sorrend[j]);
        swap(hely[sorrend[i]], hely[sorrend[j]]);
      }
    }
  }

  // az esemenyek megfelelo sorrendben
  sort(e.begin(), e.end());
  for (auto p : e) {
    bool id = p.first.second;
    int a = p.second.first, b = p.second.second;
    if (id == 0) {
      // az a. auto megelozi a b. autot
      // ha egy pillanatban 3 sorrendje cserelodik meg (abc)->(cba) akkor
      // lehetnek nehezsegek, ezert nem eleg csak siman kicserelni a ket autot
      if (hely[a] < hely[b])
        continue;
      else {
        swap(hely[a], hely[b]);
        swap(sorrend[hely[a]], sorrend[hely[b]]);
      }
    }
    if (id == 1) {
      // itt kell valaszolni valamelyik kerdesre
      valasz[b] = sorrend[a];
    }
  }

  for (int i = 1; i <= q; i++) {
    cout << valasz[i] << "\n";
  }
  return 0;
}
