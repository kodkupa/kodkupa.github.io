/*
Adott sor kvazi-izogram, ha barmely benne elofordulo betu gyakorisaga legfeljebb 2.
A gyakorisagok szamontartasahoz hasznalhatunk peldaul tombot vagy szotarat (std::map vagy std::unordered_map).
Fontos, hogy csak a betukkel foglalkozzunk, az egyeb karaktereket hagyjuk figyelmen kivul.
*/

#include <bits/stdc++.h>
using namespace std;
int n, ans;
string tmp;

bool quasi_isogram(string &tmp)
{
    int cnt[26] = {0};
    for (char c: tmp)
    {
        if (c >= 'a' && c <= 'z') cnt[c - 'a']++;
        if (c >= 'A' && c <= 'Z') cnt[c - 'A']++;
    }
    for (int i = 0; i < 26; ++i)
    {
        if (cnt[i] > 2) return false;
    }
    return true;
}

int main()
{
    cin >> n;
    getline(cin, tmp);
    for (int i = 0; i < n; ++i)
    {
        getline(cin, tmp);
        if (quasi_isogram(tmp)) ans++;
    }
    cout << ans << "\n";
}