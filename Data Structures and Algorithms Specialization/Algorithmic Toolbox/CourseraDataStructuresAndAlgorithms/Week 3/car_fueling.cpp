#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, vector<int>& stops) {

	// write your code here
	int refills = 0;
	int currentRefill = 0;
	while (currentRefill < stops.size()-1) {
		int lastRefill = currentRefill;
		while (currentRefill < stops.size()-1 && stops[currentRefill + 1] - stops[lastRefill] <= tank) {
			currentRefill += 1;
		}
		if (currentRefill == lastRefill)
			return -1;

		if (currentRefill < stops.size()-1)
			refills += 1;

	}
	return refills;
}


int main() {
	int d = 0;
	cin >> d;
	int m = 0;
	cin >> m;
	int n = 0;
	cin >> n;

	vector<int> stops(n + 2);
	for (size_t i = 1; i <= n; ++i)
		cin >> stops.at(i);
	stops[n + 1] = d;

	cout << compute_min_refills(d, m, stops) << "\n";

	return 0;
}
