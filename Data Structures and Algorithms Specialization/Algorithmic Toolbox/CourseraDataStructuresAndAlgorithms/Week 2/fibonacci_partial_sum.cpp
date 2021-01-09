#include <iostream>
#include <vector>

int get_fibonacci_partial_sum_fast(long long from, long long to) {

	std::vector<int> fib_seq(61);
	fib_seq[0] = 0; fib_seq[1] = 1;
	for (int i = 2; i < 61; i++) {
		fib_seq[i] = (fib_seq[i - 1] + fib_seq[i - 2]) % 10;
	}
	int from_index = from % 60;
	int to_index = to % 60;
	int sum = 0, partial_sum1 = 0, partial_sum2 = 0;
	for (std::vector<int>::iterator it = fib_seq.begin(); it != fib_seq.end(); it++) {
		sum += *it;
		if (it == fib_seq.begin() + from_index - 1) {
			partial_sum1 = sum;
		}
		if (it == fib_seq.begin() + to_index) {
			partial_sum2 = sum;
		}
	}
	return ((to / 60) * sum + partial_sum2 - ((from / 60) * sum + partial_sum1)) % 10;
}

int main() {
	long long from, to;
	std::cin >> from >> to;
	std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
}
