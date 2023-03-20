// @check-accepted: examples no-limits
#include <iostream>

static void move(int amount, int from, int to) {
    std::cout << amount << ' ' << from << ' ' << to << '\n';
}

int main() {
    int n;
    std::cin >> n;

    for (int i = 0; i < (n + 1) / 2; ++i) {
        move(1, 0, 1);
    }
    move(n / 2, 0, 1);
	for (int i = 0; i < n / 2; ++i) {
		move(1, 1, 0);
	}
    move(n / 2, 0, 1);
}
