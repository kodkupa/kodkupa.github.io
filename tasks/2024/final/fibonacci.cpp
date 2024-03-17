#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> fib {2,3};

unordered_map<int,int> memo { {1, 1} };
int f(int x) {
    if(memo.find(x) != memo.end()) return memo[x];

    for(int i : fib) {
        if(x % i == 0) {
            memo[x] += f(x/i);
        }
    }

    return memo[x];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    while(fib.back() <= 1e9) {
        fib.push_back(fib.back() + fib[fib.size()-2]);
    }

    int T; cin >> T;
    while(T--) {
        int M; cin >> M;
        cout << f(M) << endl;
    }

    return 0;
}