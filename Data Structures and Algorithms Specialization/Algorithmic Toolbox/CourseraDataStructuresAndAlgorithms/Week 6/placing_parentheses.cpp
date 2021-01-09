#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include <limits.h>

using std::vector;
using std::string;
using std::max;
using std::min;

long long eval(long long a, long long b, char op) {
	if (op == '*') {
		return a * b;
	}
	else if (op == '+') {
		return a + b;
	}
	else if (op == '-') {
		return a - b;
	}
	else {
		assert(0);
	}
}


long long get_maximum_value(const string& exp) {

	size_t size = exp.size() / 2 + 1;
	vector<vector<long long>> m(size, vector<long long>(size)), M(size, vector<long long>(size));
	for (int i = 0, j = 0; i < exp.size() / 2 + 1 && j < exp.size(); i++, j += 2) {
		m[i][i] = M[i][i] = std::atoll(&exp[j]);
	}
	for (int s = 1; s < size; s++) {
		for (int i = 0; i < size - s; i++) {
			int j = i + s;
			long long min = INT_MAX;
			long long max = INT_MIN;
			for (int k = i; k < j; k++) {
				long long a = eval(M[i][k], M[k + 1][j], exp[2 * k + 1]);
				long long b = eval(M[i][k], m[k + 1][j], exp[2 * k + 1]);
				long long c = eval(m[i][k], m[k + 1][j], exp[2 * k + 1]);
				long long d = eval(m[i][k], M[k + 1][j], exp[2 * k + 1]);
				min = std::min(std::min(min, a), std::min(std::min(b, c), d));
				max = std::max(std::max(max, a), std::max(std::max(b, c), d));
			}
			m[i][j] = min; M[i][j] = max;
		}
	}
	return M[0][size - 1];
}

int main() {
	string s;
	std::cin >> s;
	std::cout << get_maximum_value(s) << '\n';
}
