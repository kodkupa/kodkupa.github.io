/*
Minden kockara szimulaljuk a jatekot. 
Az i-edik kockaval dobva egy kor soran eloszor i-t lepunk, majd addig ugralunk elore, amig az alabbi ket feltetel mindegyike teljesul:
1. Nem ertunk a palya vegere.
2. Az ugrani kivant hossz pozitiv (azaz nem 0).
*/

#include <bits/stdc++.h>
using namespace std;
const int N = 1e5;
int n, j[N];

int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> j[i];
    for (int i = 1; i <= 6; ++i)
    {
        int p = 0, a = 0;
        while (p < n)
        {
            p += i, a++;
            while (p < n && j[p] != 0) p += j[p];
        }
        cout << a << " ";
    }
}