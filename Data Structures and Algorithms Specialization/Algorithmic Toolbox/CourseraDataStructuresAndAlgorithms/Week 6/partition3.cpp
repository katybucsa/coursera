#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using std::vector;

int optimal_value(int V, const vector<int>& A) {

	vector<vector<int>> max_weights(A.size() + 1, vector<int>(V + 1));

	for (int i = 1; i <= A.size(); i++) {
		for (int w = 1; w <= V; w++) {
			max_weights[i][w] = max_weights[i - 1][w];
			if (A[i - 1] <= w) {
				int weight = max_weights[i - 1][w - A[i - 1]] + A[i - 1];
				if (max_weights[i][w] < weight) {
					max_weights[i][w] = weight;
				}
			}
		}
	}
	return max_weights[A.size()][V];
}

int partition3(vector<int>& A) {

	if (std::accumulate(A.begin(), A.end(), 0) % 3 != 0)
		return 0;

	int V = std::accumulate(A.begin(), A.end(), 0) / 3;
	int v1 = optimal_value(V, A);
	int v2 = optimal_value(2 * V, A);
	return V == v1 && v2 == 2 * v1;
}

int main() {
	int n;
	std::cin >> n;
	vector<int> A(n);
	for (size_t i = 0; i < A.size(); ++i) {
		std::cin >> A[i];
	}
	std::cout << partition3(A) << '\n';
}