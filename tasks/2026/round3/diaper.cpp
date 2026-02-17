// @check-accepted: *
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int milk = 0, food = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        if (milk >= 50) {
            ans++; milk -= 50;
        } else if (food >= 80) {
            ans++; food -= 80;
        }
        int f; char t;
        cin >> f >> t;
        if (t == 'M') milk += f;
        else food += f;
    }

    cout << ans << endl;
    return 0;
}
