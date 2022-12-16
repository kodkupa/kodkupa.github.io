// strud. Vlad-Mihai Bogdan - University of Bucharest
// O(N * M)

#include <bits/stdc++.h>
using namespace std;

const int MOD1 = 1'000'000'000;
const int MOD2 = 1'000'000'007;
const int BASE1 = 17;
const int BASE2 = 19;

struct HashPair {
	int operator()(const pair<int, int> &p) const {
		if (p.first != p.second) {
			return p.first ^ p.second;
		}
		
		return p.first;
	}
};

string minimalRotation(const string &s) {
    int N = (int)s.size();
    int minPos = 0, l = 0, p = 1;
    while (p < N && minPos + l + 1 < N) {
        if (s[minPos + l] == s[(p + l) % N]) {
            l++;
        } else if (s[minPos + l] < s[(p + l) % N]) {
            p = p + l + 1;
            l = 0;
        } else {
            minPos = max(minPos + l + 1, p);
            p = minPos + 1;
            l = 0;
        }
    }
    
    string ans;
    for (int i = minPos; (int)ans.size() != N; i = (i + 1) % N) {
        ans.push_back(s[i]);
    }
    return ans;
}

pair<int, int> stringHash(const string &s) {
    int a = 0, b = 0, p1 = 1, p2 = 1;
    for (const char &c : s) {
        a = ((long long)p1 * c + a) % MOD1;
        b = ((long long)p2 * c + b) % MOD2;
        p1 = (long long)p1 * BASE1 % MOD1;
        p2 = (long long)p2 * BASE2 % MOD2;
    }
    
    return make_pair(a, b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int N, M; cin >> N >> M;
    
    unordered_map<pair<int, int>, int, HashPair> mp;

long long answer = 0;
    for (int i = 0; i < N; i++) {
        string s; cin >> s;
        
        string t = minimalRotation(s);
        auto h = stringHash(t);
        mp[h]++;
        answer += mp[h] - 1;
        
        /*if (i > 0) {
			cout << " ";
		}
		cout << mp[h] - 1;*/
    }
    
    cout << answer;
    cout << endl;

    return 0;
}
