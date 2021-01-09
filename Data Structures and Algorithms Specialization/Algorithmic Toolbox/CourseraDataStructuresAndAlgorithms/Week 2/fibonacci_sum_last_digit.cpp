#include <iostream>
#include <vector>

int fibonacci_sum_fast(long long n) {

	std::vector<int> fib_row(61);
	fib_row[0] = 0;
	fib_row[1] = 1;
	for (int i = 2; i <= 60; i++) {
		fib_row[i] = (fib_row[i - 1] + fib_row[i - 2]) % 10;
	}
	int sum = 0, part_sum = 0;
	for (std::vector<int>::iterator it = fib_row.begin(); it != fib_row.end(); ++it) {
		sum += *it;
		if (it == fib_row.begin() + n % 60)
			part_sum = sum;
	}

	return ((n / 60) * sum + part_sum) % 10;
}

int main() {
	long long n = 0;
	std::cin >> n;
	std::cout << fibonacci_sum_fast(n);
}
