#include <iostream>
#include <vector>

using std::vector;

int optimal_weight(int W, const vector<int>& weights) {

	vector<vector<int>> max_weights(weights.size() + 1, vector<int>(W + 1));

	for (int i = 1; i <= weights.size(); i++) {
		for (int w = 1; w <= W; w++) {
			max_weights[i][w] = max_weights[i - 1][w];
			if (weights[i - 1] <= w) {
				int weight = max_weights[i - 1][w - weights[i - 1]] + weights[i - 1];
				if (max_weights[i][w] < weight) {
					max_weights[i][w] = weight;
				}
			}
		}
	}
	return max_weights[weights.size()][W];
}

int main() {
	int n, W;
	std::cin >> W >> n;
	vector<int> w(n);
	for (int i = 0; i < n; i++) {
		std::cin >> w[i];
	}
	std::cout << optimal_weight(W, w) << '\n';
}
