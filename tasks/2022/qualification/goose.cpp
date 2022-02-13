/*
Minden kockára szimuláljuk a játékot. 
Az i-edik kockával dobva egy kör során először i-t lépünk, majd addig ugrálunk előre, amíg az alábbi két feltétel mindegyike teljesül:
1. Nem értünk a pálya végére.
2. Az ugrani kívánt hossz pozitív (azaz nem 0).
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