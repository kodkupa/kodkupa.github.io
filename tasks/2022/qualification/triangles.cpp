// Triangles solution

// For the smaller subtasks, we can solve the problem using brute force, fixing
// two or three points and checking how many right triangles we have there.

// For the full solution, we can fix each of the points from the input, and
// count how many points are there with the same x coordinate and same y
// coordinate. In order to compute this fast, we will store using frequency
// arrays how many points we got for each possible x and y coordinate and thus,
// the final complexity would be O(n).

#include <bits/stdc++.h>

#define ll long long int

using namespace std;

ll xcnt[200005];
ll ycnt[200005];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> xs(n);
    vector<int> ys(n);
    for (int i = 0; i < n; i++)
    {
        cin >> xs[i] >> ys[i];
        xcnt[xs[i]]++;
        ycnt[ys[i]]++;
    }

    ll ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans += (xcnt[xs[i]] - 1) * (ycnt[ys[i]] - 1);
    }
    cout << ans;
}