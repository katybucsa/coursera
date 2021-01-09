#include <iostream>

long long gcd_fast(long long a, long long b) {

	if (b != 0)
		return gcd_fast(b, a % b);
	return a;

}

int main() {

	long long a, b;
	std::cin >> a >> b;
	if (b > a) {
		std::swap(a, b);
	}
	std::cout << gcd_fast(a, b) << std::endl;
	return 0;
}
