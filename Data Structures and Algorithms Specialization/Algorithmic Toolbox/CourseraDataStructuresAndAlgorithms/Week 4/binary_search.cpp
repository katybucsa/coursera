#include <iostream>
#include <cassert>
#include <vector>

using std::vector;

int binary_search(const vector<int>& a, int x) {

	int left = 0, right = a.size()-1;
	while (left <= right) {
		int m = left + (right - left) / 2;
		if (a[m] == x)
			return m;
		if (x < a[m])
			right = m - 1;
		else
			left = m + 1;
	}
	return -1;
}

int linear_search(const vector<int>& a, int x) {
	for (size_t i = 0; i < a.size(); ++i) {
		if (a[i] == x) return i;
	}
	return -1;
}

int main() {
	int n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); i++) {
		std::cin >> a[i];
	}
	int m;
	std::cin >> m;
	vector<int> b(m);
	for (int i = 0; i < m; ++i) {
		std::cin >> b[i];
	}
	for (int i = 0; i < m; ++i) {

		std::cout << binary_search(a, b[i]) << ' ';
	}
}
