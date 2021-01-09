#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

int lcs2(vector<int>& a, vector<int>& b) {

	vector<vector<int>> lenghts(a.size() + 1, vector<int>(b.size() + 1));

	for (int j = 1; j <= b.size(); j++) {
		for (int i = 1; i <= a.size(); i++) {
			if (a[i - 1] == b[j - 1])
				lenghts[i][j] = lenghts[i - 1][j - 1] + 1;
			else if (lenghts[i - 1][j] > lenghts[i][j - 1])
				lenghts[i][j] = lenghts[i - 1][j];
			else
				lenghts[i][j] = lenghts[i][j - 1];
		}
	}
	return lenghts[a.size()][b.size()];
}

int main() {
	size_t n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> a[i];
	}

	size_t m;
	std::cin >> m;
	vector<int> b(m);
	for (size_t i = 0; i < m; i++) {
		std::cin >> b[i];
	}
	std::cout << lcs2(a, b) << std::endl;
}
