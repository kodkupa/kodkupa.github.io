// @check-accepted: Examples n<=20 n<=2000 n<=200000 n<=10^18
#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;
 
long long n;
const int mod = 1000000007; 
 
long long a[5];
long long mat[5][5];
void mult(long long a[5][5], long long b[5][5])
{
    long long ans[5][5];
    for(long long i = 1; i <= 2; ++i)
        for(long long j = 1; j <= 2; ++j)
            ans[i][j] = 0;
    for(long long i = 1; i <= 2; ++i)
        for(long long j = 1; j <= 2; ++j)
            for(long long k = 1; k <= 2; ++k)
                ans[i][j] = (ans[i][j] + a[i][k] * b[k][j]) % mod;
    for(long long i = 1; i <= 2; ++i)
        for(long long j = 1; j <= 2; ++j)
            a[i][j] = ans[i][j];
}
void lgput(long long a[5][5], long long p)
{
    long long cpy[5][5];
    for(long long i = 1; i <= 2; ++i)
        for(long long j = 1; j <= 2; ++j)
        {
            cpy[i][j] = a[i][j];
            if(i == j)
                a[i][j] = 1;
            else
                a[i][j] = 0;
        }
    while(p)
    {
        if(p & 1)
            mult(a, cpy);
        mult(cpy, cpy);
        p >>= 1;
    }
}

long long solve(long long nrd)
{
    memset(a, 0, sizeof(a));
    memset(mat, 0, sizeof(mat));
    
    a[1] = 2, a[2] = 0;
    mat[1][1] = 1, mat[1][2] = 2;
    mat[2][1] = 1, mat[2][2] = 0;
    if(nrd <= 2)
        return a[3 - nrd];
    else
    {
        lgput(mat, nrd - 2);
        long long ans[4];
        for(int j = 1; j <= 2; ++j)
            ans[j] = 0;
        for(int i = 1; i <= 2; ++i)
            for(int k = 1; k <= 2; ++k)
                ans[i] = (ans[i] + mat[i][k] * a[k]) % mod;
        return ans[1];
    }
}
int main()
{
    int t;
    cin >> t;
    
    for(; t; t--)
    {
        cin >> n;
        assert(n <= 1e18);
        cout << solve(n) << '\n';
    }
    return 0;
}
