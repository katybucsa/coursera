#include <iostream>
#include <vector>
#include <limits.h>

int get_change(int m) {

	std::vector<int> coins = { 1,3,4 };
	std::vector<int> minNumCoins(m + 1);
	for (int i = 1; i <= m; i++) {
		minNumCoins[i] = INT_MAX;
		for (int j = 0; j < coins.size(); j++) {
			if (i >= coins[j]) {
				int numCoins = minNumCoins[i - coins[j]] + 1;
				if (numCoins < minNumCoins[i]) {
					minNumCoins[i] = numCoins;
				}
			}
		}
	}
	return minNumCoins[m];
}

int main() {
	int m;
	std::cin >> m;
	std::cout << get_change(m) << '\n';
}
