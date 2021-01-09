#include <iostream>
#include <vector>
#include <algorithm>

int fibonacci_sum_squares_naive(long long n) {
	if (n <= 1)
		return n;

	long long previous = 0;
	long long current = 1;
	long long sum = 1;

	for (long long i = 0; i < n - 1; ++i) {
		long long tmp_previous = previous;
		previous = current;
		current = tmp_previous + current;
		sum += current * current;
	}

	return sum % 10;
}

int rest_square_op(int i) {

	return (i * i) % 10;
}
int fibonacci_sum_squares_fast(long long n) {

	if (n <= 1)
		return n;

	std::vector<int> fib_seq(61);
	fib_seq[0] = 0; fib_seq[1] = 1;
	for (int i = 2; i < 61; i++) {
		fib_seq[i] = (fib_seq[i - 1] + fib_seq[i - 2]) % 10;
	}
	std::transform(fib_seq.begin(), fib_seq.end(), fib_seq.begin(), rest_square_op);

	int sum = 0, part_sum = 0;
	for (std::vector<int>::iterator it = fib_seq.begin(); it != fib_seq.end(); it++) {
		sum += *it;
		if (it == fib_seq.begin() + n % 60)
			part_sum = sum;
	}
	return ((n / 60) * sum + part_sum) % 10;
}

int main() {
	long long n = 0;
	std::cin >> n;
	std::cout << fibonacci_sum_squares_fast(n);
}
