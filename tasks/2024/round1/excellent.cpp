// insert brief description of the solution here

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
    
    if (N % 2 == 0) {
        for (int i = 0; i < N; ++i)
            cout << (i % 2 ? "1" : "5");
    } else if (N % 3 == 0) {
        for (int i = 0; i < N; ++i)
            cout << "1";
    } else if (N % 3 == 2) {
        for (int i = 2; i < N; ++i)
            cout << "1";
        cout << "15";
    } else if (N % 3 == 1 and N>1) {
        for (int i = 4; i < N; ++i)
            cout << "1";
        cout << "1515";
    } else {
        cout << "-1";
    }

    cout << endl;
    return 0;
}
