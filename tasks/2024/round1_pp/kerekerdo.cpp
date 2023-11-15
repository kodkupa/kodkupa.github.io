// @check-accepted: examples N5 N100 full
#include <iostream>
using namespace std;

int main() {
    int n,a,b;
    cin>>n>>a>>b;
    int fak;
    if(a<=b) {
        fak=b-a+1;
    }else {
        fak=n-a+b+1;
    }

    if(fak<5) {
        cout<<"Tul konnyu!\n";
    }else {
        cout<<fak<<"\n";
    }

    return 0;
}
