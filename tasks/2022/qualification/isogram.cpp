/*
Adott sor kvázi-izogram, ha bármely benne előforduló betű gyakorisága legfeljebb 2.
A gyakoriságok számontartásához használhatunk például tömböt vagy szótárat (std::map vagy std::unordered_map).
Fontos, hogy csak a betűkkel foglalkozzunk, az egyéb karaktereket hagyjuk figyelmen kívül.
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