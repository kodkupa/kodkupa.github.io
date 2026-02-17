// @check-accepted: examples NQbrute DSmall NoSweetness no-limits
/*
As the sweetness factors are small enough, maintain
frequency[i] = count of how many desserts use P and have sweetness = i
The preference query just becomes checking that
frequency[l] + frequency[l + 1] + ... + frequency[r] >= k
This can be done using a prefix sum on this query

Complexity O(N + Q) with O(Smax) prerequisite computation complexity
(or O(N + Q + Smax) if you'd like)
*/
#include <iostream>
#include <cassert>

using namespace std;

const int VMAX = 1e6;
const int NMAX = 1e5;

int fr[2 * VMAX + 1]; //frequency[i] but scaled from [-Smax, Smax] to [0, 2 Smax]
int s[2 * VMAX + 1]; //its prefix sum

struct dessert
{
    int s, f;
};

dessert v[NMAX + 1];

int main()
{
    int i, n, p;
    cin >> n >> p;
    int *freq = fr + VMAX; //trick for having negative indexes
    int *sp = s + VMAX; //idem
    for (i = 1; i <= n; i++)
        cin >> v[i].s;
    for (i = 1; i <= n; i++)
        cin >> v[i].f;
    //freq computation 
    for (i = 1; i <= n; i++)
        if (v[i].f == p)
            freq[v[i].s]++;
    //prefix sum computation
    s[0] = fr[0];
    for (i = 1; i <= 2 * VMAX; i++)
        s[i] = s[i - 1] + fr[i];
    int q;
    cin >> q;
    while (q--)
    {
        int l, r, k;
        cin >> l >> r >> k;
        int exterior = 0;
        if (l != -VMAX)
            exterior = sp[l - 1];
        if (sp[r] - exterior >= k) 
            cout << "YES";
        else
            cout << "NO";
        cout << "\n";
    }
    return 0;
}
