#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {

	double value = 0.0;
	if (capacity == 0)
		return value;
	for (int i = 0; i < weights.size(); i++) {
		int a = weights[i] < capacity ? weights[i] : capacity;
		value += a * (double)values[i] / weights[i];
		weights[i] -= a;
		capacity -= a;
	}

	return value;
}


int main() {

	int n;
	int capacity;
	std::cin >> n >> capacity;
	vector<int> values(n);
	vector<int> weights(n);
	vector<std::pair<int, int>> raport(n);
	for (int i = 0; i < n; i++) {
		std::cin >> values[i] >> weights[i];
		raport[i] = std::make_pair(values[i], weights[i]);
	}
	std::sort(raport.begin(), raport.end(), [](std::pair<int, int> p1, std::pair<int, int> p2) {return (double)p1.first / p1.second > (double)p2.first / p2.second; });
	for (int i = 0; i < raport.size(); i++) {
		values[i] = raport[i].first;
		weights[i] = raport[i].second;
	}

	double optimal_value = get_optimal_value(capacity, weights, values);

	std::cout.precision(10);
	std::cout << std::fixed << optimal_value << std::endl;
	return 0;
}
