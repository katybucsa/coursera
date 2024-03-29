#include <iostream>
#include <vector>

using std::vector;
//if remaining is grater than the last element in the array
vector<int> optimal_summands(int n) {

	vector<int> summands;
	int number = 1;
	while (n) {
		if (n - number > number || n-number==0) {
			summands.push_back(number);
			n -= number;
		}
		number++;
	}
	return summands;
}

int main() {
	int n;
	std::cin >> n;
	vector<int> summands = optimal_summands(n);
	std::cout << summands.size() << '\n';
	for (size_t i = 0; i < summands.size(); ++i) {
		std::cout << summands[i] << ' ';
	}
}
