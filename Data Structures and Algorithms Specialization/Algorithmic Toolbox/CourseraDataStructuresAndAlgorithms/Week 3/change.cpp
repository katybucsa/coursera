#include <iostream>

int get_change(int m) {
	//write your code here

	if (m == 1 || m == 5 || m == 10)
		return 1;
	return m / 10 + (m % 10) / 5 + (m % 10) % 5;
}

int main() {
	int m;
	std::cin >> m;
	std::cout << get_change(m) << '\n';
}
