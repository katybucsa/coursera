
#include <iostream>
#include <vector>

int last_digit_fibonacci_fast(long long n) {

	if (n <= 1)
		return n;
	std::vector<int> fib_row(61);
	fib_row[0] = 0;
	fib_row[1] = 1;
	for (int i = 2; i <= 60; i++) {
		fib_row[i] = (fib_row[i - 1] + fib_row[i - 2]) % 10;
	}
	return fib_row[n % 60];
}


int main() {

	long long n;
	std::cin >> n;
	std::cout << last_digit_fibonacci_fast(n) << '\n';
}
