#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::swap;

int partition2(vector<int>& a, int l, int r) {

	int x = a[l];
	int j = l;
	for (int i = l + 1; i <= r; i++) {
		if (a[i] <= x) {
			j++;
			swap(a[i], a[j]);
		}
	}
	swap(a[l], a[j]);
	return j;
}

std::pair<int, int> partition3(vector<int>& a, int l, int r) {

	int x = a[l];
	int j = l;
	for (int i = l + 1; i <= r; i++) {
		if (a[i] < x) {
			swap(a[j], a[i]);
			j++;
		}
		else
			if (a[i] > x) {
				swap(a[i], a[r]);
				r--;
				i--;
			}
	}
	return std::make_pair(j, r);

}


void randomized_quick_sort(vector<int>& a, int l, int r) {

	if (l >= r) {
		return;
	}

	int k = l + rand() % (r - l + 1);
	swap(a[l], a[k]);
	int m = partition2(a, l, r);

	randomized_quick_sort(a, l, m - 1);
	randomized_quick_sort(a, m + 1, r);
}

void randomized_quick_sort3(vector<int>& a, int l, int r) {

	if (l >= r) {
		return;
	}

	int k = l + rand() % (r - l + 1);
	swap(a[l], a[k]);
	std::pair<int, int> p = partition3(a, l, r);

	randomized_quick_sort3(a, l, p.first - 1);
	randomized_quick_sort3(a, p.second + 1, r);
}

int main() {

	int n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); ++i) {
		std::cin >> a[i];
	}

	randomized_quick_sort3(a, 0, a.size() - 1);
	for (size_t i = 0; i < a.size(); ++i) {
		std::cout << a[i] << ' ';
	}

	//while (true) {
	//	n = rand() % 10+5;
	//	vector<int> a(n);
	//	for (size_t i = 0; i < a.size(); ++i) {
	//		a[i] = rand() % 100;
	//		std::cout << a[i] << ' ';
	//	}
	//	std::cout << std::endl;
	//	vector<int> b(a);
	//	/*a = { 23,29,29,65,59,32 };
	//	b = { 23,29,29,65,59,32 };*/
	//	randomized_quick_sort(a, 0, a.size() - 1);
	//	randomized_quick_sort3(b, 0, a.size() - 1);
	//	for (size_t i = 0; i < a.size(); ++i) {
	//		std::cout << a[i] << ' ';
	//	}
	//	std::cout << std::endl;
	//	for (size_t i = 0; i < b.size(); ++i) {
	//		std::cout << b[i] << ' ';
	//	}
	//	if (a != b)
	//		break;
	//	std::cout << std::endl << std::endl;
	//}
}