#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;


vector<int> merge_v(vector<int>& b, vector<int>& c) {

	vector<int> d(b.size() + c.size());
	int i = 0, j = 0, k = 0;
	while (i < b.size() && j < c.size()) {
		if (b[i] < c[j]) {
			d[k] = b[i];
			i++;
		}
		else {
			d[k] = c[j];
			j++;
		}
		k++;
	}
	while (i < b.size()) {
		d[k] = b[i];
		i++; k++;
	}
	while (j < c.size()) {
		d[k] = c[j];
		j++; k++;
	}
	return d;
}


vector<int> merge_sort(vector<int>& a, int left, int right) {

	if (left == right) {
		vector<int> a1(a.begin() + left, a.begin() + right + 1);
		return a1;
	}

	int m = (left + right) / 2;
	vector<int> b = merge_sort(a, left, m);
	vector<int> c = merge_sort(a, m + 1, right);

	return merge_v(b, c);
}

int get_majority_element(vector<int>& a, int left, int right) {

	if (left == right) return -1;
	if (left + 1 == right) return a[left];

	a = merge_sort(a, left, right - 1);
	int max_count = 1, count = 1;
	for (int i = 0; i < a.size() - 1; i++) {
		if (a[i] == a[i + 1]) {
			count++;
		}
		else if (count > max_count) {
			max_count = count;
			count = 1;
		}
	}

	if (max_count > a.size() / 2 || count > a.size() / 2)
		return 1;
	return -1;
}

 WITHOUT SORTING
int get_majority_element(vector<int>& a, int left, int right) {
    if (left == right) return -1;
    if (left + 1 == right) return a[left];

    int left_elem = get_majority_element(a, left, (left + right - 1) / 2 + 1);
    int right_elem = get_majority_element(a, (left + right - 1) / 2 + 1, right);

    int lcount = 0;
    for (int i = left; i < right; i++) {
        if (a[i] == left_elem) lcount += 1;
    }
    if (lcount > (right - left) / 2) return left_elem;

    int rcount = 0;
    for (int i = left; i < right; i++) {
        if (a[i] == right_elem) rcount += 1;
    }
    if (rcount > (right - left) / 2) return right_elem;

    return -1;
}



int get_majority_element_optim(vector<int>& a) {

	int index = 0;
	int count = 1;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == a[index])
			count++;
		else
			count--;
		if (count == 0) {
			index = i;
			count = 1;
		}
	}

	int appearances = 0;
	for (int i = 0; i < a.size(); i++)
		if (a[i] == a[index])
			appearances++;
	return appearances > a.size() / 2;
}

int main() {
	int n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); ++i) {
		std::cin >> a[i];
	}
	std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
	//std::cout << get_majority_element_optim(a) << '\n';
}
