// @check-accepted: examples N<=5 N<=1000 no-limits

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // uncomment the following lines if you want to read/write from files
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");

    int N;
    cin >> N;

    int L = -1, tot = 0;


    for (int i = 1; tot <= N; i++) {
        tot += i * i;
        L++;
    }


    cout << L << endl;

    return 0;
}
