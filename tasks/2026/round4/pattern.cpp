/*
Order the points in both drawing and pattern
by first coordinate (or second, doesn't matter)
Then a (dx, dy) vector that generates a pattern in the drawing will
always map first point extremity to first point extremity, because
you add the same values to both coordinates you want to compare

Fix the segment that must be first in the pattern and calculate
dx and dy. Afterwards, just check that the rest of the segments
exist in the drawing using a STL set container.

Complexity O(NS log N).
*/
#include <iostream>
#include <cassert>
#include <set>
#define ll long long
using namespace std;

const int SMAX = 50;
const int NMAX = 1e5;

struct point
{
    int x, y;
    point (int a, int b)
    {
        x = a;
        y = b;
    }
    point()
    {

    }
};

bool operator <(point a, point b)
{
    if (a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}

bool operator ==(point a, point b)
{
    return a.x == b.x and a.y == b.y;
}

bool operator !=(point a, point b)
{
    return !(a == b);
}

struct segment
{
    point first, second;
    segment(point a, point b)
    {
        first = a;
        second = b;
    }
    segment()
    {

    }
};

bool operator <(segment a, segment b)
{
    if (a.first != b.first)
        return a.first < b.first;
    return a.second < b.second;
}

segment pattern[SMAX + 1];
segment drawing[NMAX + 1];

void read(segment &seg)
{
    cin >> seg.first.x >> seg.first.y;
    cin >> seg.second.x >> seg.second.y;
    if (seg.second < seg.first)
        swap(seg.first, seg.second);
}

set <segment> ds;

int main()
{
    int i, j;
    int s, n;
    cin >> s;
    for (i = 1; i <= s; i++)
        read(pattern[i]);
    cin >> n;
    for (i = 1; i <= n; i++)
    {
        read(drawing[i]);
        ds.insert(drawing[i]);
    }
    int ans = 0;
    for (i = 1; i <= n; i++)
    {
        int dx = drawing[i].first.x - pattern[1].first.x;
        int dy = drawing[i].first.y - pattern[1].first.y;

        int nx = pattern[1].second.x + dx;
        int ny = pattern[1].second.y + dy;
        bool ok = (drawing[i].second == point(nx, ny));

        for (j = 2; ok and j <= s; j++)
        {
            int nx1, ny1, nx2, ny2;

            nx1 = pattern[j].first.x + dx;
            ny1 = pattern[j].first.y + dy;

            nx2 = pattern[j].second.x + dx;
            ny2 = pattern[j].second.y + dy;

            segment to_check(point(nx1, ny1), point(nx2, ny2));

            ok &= (ds.find(to_check) != ds.end());
        }
        if (ok)
            ans++;
    }
    cout << ans << "\n";
    return 0;
}
