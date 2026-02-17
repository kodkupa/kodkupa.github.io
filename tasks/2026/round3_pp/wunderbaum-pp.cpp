// @check-accepted: examples NsmallnoL Nsmall Nmid no-limits
// insert brief description of the solution here

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // uncomment the following lines if you want to read/write from files
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");

    int l, n; cin>>l>>n;
    for(int i = 1; i <= n; i++){
        if(i%3 == 0) l += 3;
        else if(i%2 == 0) l += 2;
        else l += 1;
    }

    cout<<l<<endl;


    return 0;
}
