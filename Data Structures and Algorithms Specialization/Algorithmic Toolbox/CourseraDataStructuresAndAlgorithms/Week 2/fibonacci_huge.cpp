#include <iostream>
#include <vector>


// Pisano period Fi modulo m
long long length_pisano_period(long long m) {

	std::vector<long long> fib_seq(m * m + 2);
	fib_seq[0] = 0; fib_seq[1] = 1;
	for (long long i = 2; i <= m * m + 1; i++) {
		fib_seq[i] = (fib_seq[i - 1] + fib_seq[i - 2]) % m;
		if (fib_seq[i] == 1 && fib_seq[i - 1] == 0) {//Pisano period starts with 01
			return i - 1;
		}
	}
}

long long get_fibonacci_huge_fast(long long n, long long m) {

	n = n % length_pisano_period(m);
	if (n <= 1)
		return n;

	std::vector<long long> fib_seq(n + 1);
	fib_seq[0] = 0;
	fib_seq[1] = 1;
	for (int i = 2; i <= n; i++) {
		fib_seq[i] = (fib_seq[i - 1] + fib_seq[i - 2]) % m;
	}
	return fib_seq.at(n) % m;
}

int main() {
	long long n, m;
	std::cin >> n >> m;
	std::cout << get_fibonacci_huge_fast(n, m) << '\n';
}
