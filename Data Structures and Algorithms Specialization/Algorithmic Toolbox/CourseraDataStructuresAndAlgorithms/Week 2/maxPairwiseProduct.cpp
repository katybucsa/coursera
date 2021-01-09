#include <iostream>
#include <vector>

long long max_pairwise_product(std::vector<int>& numbers, int n) {

	int index1 = 0, index2 = 0;
	for (int i = 1; i < n; i++) {
		if (numbers.at(i) > numbers.at(index1)) {
			index1 = i;
		}
	}

	for (int i = 1; i < n; i++) {
		if ((numbers.at(i) > numbers.at(index2) && i != index1) || index1 == index2) {
			index2 = i;
		}
	}
	return ((long long)numbers.at(index1)) * numbers.at(index2);
}


int main() {

	int n;
	std::cin >> n;
	std::vector<int> numbers(n);
	for (int i = 0; i < n; i++) {
		std::cin >> numbers[i];
	}
	std::cout << max_pairwise_product(numbers, n);
}