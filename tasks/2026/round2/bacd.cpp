#include <iostream>
#include <vector>
using namespace std;

const long long maxn=500005, mod=1e9+7;
long long n;
long long t[maxn];

long long fen[maxn]; // Fenwick faval lehet felgyorsitani (szegmens fa ugyanugy jo)
long long lsb(long long a) {
    return (a & -a);
}
void add(long long a, long long b) {
    while (a<=n) {
        fen[a]+=b;
        a+=lsb(a);
    }
}
long long ask(long long a) {
    long long ans=0;
    while (a) {
        ans+=fen[a];
        a-=lsb(a);
    }
    return ans;
}

void solvenlogn() {
    long long inc4=0, ossz=0;
    for (long long i=1; i<=n; i++) {
        long long elott=ask(t[i]), utan=n-t[i]-(i-1)+elott;
        ossz=(ossz+elott*(elott-1)*utan/2)%mod;
        // c-t rogzitjuk, elotte hany kisebb, es utana hany nagyobb van, ezekbol megvan az 1234 + 2134
        add(t[i], 1);
    }
    for (long long i=0; i<=n; i++) {
        fen[i]=0;
    }

    vector<long long> ert(n+1, 1); // alapbol hany 1 hosszu novekvo sorozat vegzodik ott (1)

    for (long long hossz=2; hossz<=4; hossz++) {
        for (long long i=1; i<=n; i++) {
            long long regi=ert[i];
            long long kov=ask(t[i])%mod;
            ert[i]=kov; // hany hossz vegu novekvo reszsorozat vegzodik ott
            add(t[i], regi);

            if (hossz==4) {
                inc4=(inc4+kov)%mod;
            }
        }
        for (long long i=0; i<=n; i++) {
            fen[i]=0;
        }
    }



    long long ans=(ossz-inc4+mod)%mod;
    cout << ans << "\n";
}


int main() {
    cin >> n;

    for(long long i = 1; i <= n; i++)cin >> t[i];
    solvenlogn();

    return 0;
}
