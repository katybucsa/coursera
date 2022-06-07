#include <iostream>
#include <vector>
#include <deque>

using std::cin;
using std::cout;
using std::vector;

void max_sliding_window_naive(vector<int> const& A, int w) {

	std::deque<int> window, maxx;
	for (size_t i = 0; i < A.size(); ++i) {
		window.push_back(A[i]);
		if (maxx.empty())
			maxx.push_back(A[i]);
		else {
			while (!maxx.empty() && maxx.back() < A[i])
				maxx.pop_back();
			maxx.push_back(A[i]);
		}
		if (i + 1 >= w) {
			cout << maxx.front() << " ";
			if (maxx.front() == window.front())
				maxx.pop_front();
			window.pop_front();
		}
	}
}


int main() {
	int n = 0;
	cin >> n;

	vector<int> A(n);
	for (size_t i = 0; i < n; ++i)
		cin >> A.at(i);

	int w = 0;
	cin >> w;

	max_sliding_window_naive(A, w);

	return 0;
}
