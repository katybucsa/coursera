#include <iostream>
#include <vector>
#include <ctime>

long long fibonacci(int n) {//inefficient for big numbers

	std::cout << n << std::endl;
	if (n <= 1)
		return n;
	return fibonacci(n - 1) + fibonacci(n - 2);
}

long long fibonacci_faster(int n) {

	std::vector<long long> fib_row(n);
	fib_row[0] = (long long)0;
	fib_row[1] = (long long)1;
	for (int i = 2; i < n; i++) {
		fib_row[i] = fib_row[i - 1] + fib_row[i - 2];
	}
	return fib_row[n - 1];
}


int main() {

	std::cout << (double)clock() / CLOCKS_PER_SEC << std::endl;
	//std::cout << fibonacci(100); 
	std::cout << fibonacci_faster(100) << std::endl;
	std::cout << (double)clock() / CLOCKS_PER_SEC << std::endl;
}