/*Gheorghe Daniel, 100p*/
#include <iostream>
#include <vector>
using namespace std;

int N, K; 

long long check(long long X, vector<int>&A) {

    long long ans = 0;
    long long sum = 0;
    for(int i = 1; i <= N; i++) {
        sum += A[i];    
        sum = max(sum, (long long)A[i]);
        if(sum > X) {
            ans += sum - X;
            sum = X;
        }
        if(ans > 1e9) {
            return (long long)1e9 + 1;
        }
    }
    return ans;

}

int main() {
    // freopen("file.in", "r", stdin);
    // freopen("file.out", "w", stdout);

    cin.tie(0); cout.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> N >> K;


    vector<int>A(N + 3);
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    long long st = -1e16, dr = 1e16, best = 1e16;
    while(st <= dr) {
        long long mid = (st + dr) / 2;

        if(check(mid, A) <= K) {
            best = mid;
            dr = mid - 1;
        }
        else {
            st = mid + 1;
        }
    }
    cout << best << '\n';
}