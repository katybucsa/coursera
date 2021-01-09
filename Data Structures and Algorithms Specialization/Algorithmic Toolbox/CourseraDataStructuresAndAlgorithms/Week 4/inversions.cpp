#include <iostream>
#include <vector>

using std::vector;

long long merge_v(vector<int>& b, vector<int>& c, int left, int m, int right) {

	long long i = left, j = m, k = left;
	long long inversions = 0;
	while (i < m && j <= right) {
		if (b[i] <= b[j]) {
			c[k] = b[i];
			i++;
		}
		else {
			c[k] = b[j];
			inversions += m - i;
			j++;
		}
		k++;
	}
	while (i < m) {
		c[k] = b[i];
		i++; k++;
	}
	while (j <= right) {
		c[k] = b[j];
		j++; k++;
	}
	for (int i = left; i <= right; i++) {
		b[i] = c[i];
	}
	return inversions;
}

long long get_number_of_inversions(vector<int>& a, vector<int>& b, size_t left, size_t right) {

	long long number_of_inversions = 0;
	if (right <= left) return number_of_inversions;
	size_t ave = left + (right - left) / 2;
	number_of_inversions += get_number_of_inversions(a, b, left, ave);
	number_of_inversions += get_number_of_inversions(a, b, ave + 1, right);
	//write your code here
	number_of_inversions += merge_v(a, b, left, ave + 1, right);
	return number_of_inversions;
}

int main() {
	int n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); i++) {
		std::cin >> a[i];
	}
	vector<int> b(a.size());
	std::cout << get_number_of_inversions(a, b, 0, a.size() - 1) << '\n';
}
