#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;


bool isGreaterOrEqual(string first, string second) {

	return first.append(second) < second.append(first);
}

string largest_number(vector<string> a) {

	std::stringstream ret;
	while (a.size() > 0) {
		string digit = a[0];
		for (int i = 1; i < a.size(); i++)
			if (isGreaterOrEqual(digit, a[i]))
				digit = a[i];
		ret << digit;		
		auto it = std::find(a.begin(), a.end(), digit);
		if (it != a.end()) {
			a.erase(it);
		}
	}

	string result;
	ret >> result;
	return result;
}

int main() {
	int n;
	std::cin >> n;
	vector<string> a(n);
	for (size_t i = 0; i < a.size(); i++) {
		std::cin >> a[i];
	}
	std::cout << largest_number(a);
}
