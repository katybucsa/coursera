#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using std::vector;

vector<int> optimal_sequence(int n) {
	std::vector<int> sequence;
	while (n >= 1) {
		sequence.push_back(n);
		if (n % 3 == 0) {
			n /= 3;
		}
		else if (n % 2 == 0) {
			n /= 2;
		}
		else {
			n = n - 1;
		}
	}
	reverse(sequence.begin(), sequence.end());
	return sequence;
}

vector<int> get_returning_sequence(vector<int>& sequence) {

	vector<int> seq;
	seq.push_back(sequence[sequence.size() - 1]);
	while (seq.front() != 1) {
		seq.insert(seq.begin(), sequence[seq[0] - 1]);
	}
	seq.insert(seq.begin(), 1);
	return seq;
}


vector<int> optimal_sequence_dp(int n) {

	vector<int> sequence;
	vector<int> minNumOp(n + 1);
	sequence.push_back(1);
	if (n == 1)
		return sequence;

	for (int i = 2; i <= n; i++) {
		minNumOp[i] = INT_MAX;
		sequence.push_back(0);
		for (int j = 3; j >= 2; j--) {
			if (i % j == 0) {
				int numOp = minNumOp[i / j] + 1;
				if (numOp < minNumOp[i]) {
					minNumOp[i] = numOp;
					sequence[sequence.size() - 1] = i / j;
				}
			}
		}
		if (i >= 1) {
			int numOp = minNumOp[i - 1] + 1;
			if (numOp < minNumOp[i]) {
				minNumOp[i] = numOp;
				sequence[sequence.size() - 1] = i - 1;
			}
		}
	}
	return get_returning_sequence(sequence);
}

int main() {
	int n;
	std::cin >> n;
	vector<int> sequence = optimal_sequence_dp(n);
	std::cout << sequence.size() - 1 << std::endl;
	for (size_t i = 1; i < sequence.size(); ++i) {
		std::cout << sequence[i] << " ";
	}
	std::cout << n;
}
