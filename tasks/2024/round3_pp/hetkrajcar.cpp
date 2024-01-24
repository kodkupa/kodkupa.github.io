// @check-accepted: examples Teljes
// insert brief description of the solution here

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // uncomment the following lines if you want to read/write from files
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    int N, t;

    cin >> N;
    for(int i = 1; i <= N; i++)
    {
    	cin >> t;
    	if(t==7)
    	{
    		cout << i << "\n";
    		return 0;
    	}
    }
    cout << -1 << "\n";
    return 0;
}
