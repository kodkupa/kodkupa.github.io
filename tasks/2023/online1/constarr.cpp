#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using vec = vector<ll>;
using mat = vector<vec>;

const ll MOD = 1e9+7;
int M = 7;

pair<mat,mat> init(ll L, ll R) {
    vec modcnt(M);
    ll first = (L-1)/M+1, last = R/M;
    for (int i=0; i<M; ++i) {
        modcnt[i] = last - first;
        modcnt[i] += (M*last+i <= R) + (M*first-M+i >= L);
    }
    mat I(M, vec(M)), A(M, vec(M));
    for (int i=0; i<M; ++i) {
        for (int j=0; j<M; ++j) {
            I[i][j] = (i==j);
            A[i][j] = modcnt[(j+M-i)%M];
        }
    }
    return make_pair(I,A);
}
vec c0(const mat& A) {
    vec res(M, 0);
    for (int i=0; i<M; ++i) res[i] = A[i][0];
    return res;
}
vec mul(const mat& A, const vec& v) {
    vec res(M, 0);
    for (int i=0; i<M; ++i) {
        for (int j=0; j<M; ++j) {
            res[i] = (res[i] + A[i][j]*v[j]) % MOD;
        }
    }
    return res;
}
mat expand(const vec& v) {
    mat res(M, vec(M));
    for (int i=0; i<M; ++i) {
        for (int j=0; j<M; ++j) {
            res[i][j] = v[(i-j+M)%M];
        }
    }
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    ll N,L,R,K;
    cin >> N >> M >> L >> R >> K;
    
    auto [res,A] = init(L,R);
    while (N > 0) {
        if (N & 1) res = expand(mul(res, c0(A)));
        A = expand(mul(A, c0(A)));
        N >>= 1;
    }
    cout << res[0][K] << endl;

    return 0;
}