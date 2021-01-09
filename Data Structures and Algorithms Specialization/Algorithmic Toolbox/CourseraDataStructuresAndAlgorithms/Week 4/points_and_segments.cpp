#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;


class Elem {
public:
	int point;
	int type;
	int index;
	Elem(int point, int type, int index) :point{ point }, type{ type }, index{ index } {}
};

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {

	vector<int> cnt(points.size());
	vector<Elem> all;

	for (int i = 0; i < starts.size(); i++) {
		all.push_back(Elem(starts[i], 1, i));
		all.push_back(Elem(ends[i], 3, i));
	}
	for (int i = 0; i < points.size(); i++) {
		all.push_back(Elem(points[i], 2, i));
	}
	std::sort(all.begin(), all.end(), [](Elem e1, Elem e2) {
		if (e1.point == e2.point)
			return e1.type < e2.type;
		return e1.point < e2.point;
		});
	int count = 0;
	for (int i = 0; i < all.size(); i++) {
		if (all[i].type == 1)
			count++;
		else if (all[i].type == 3)
			count--;
		else
			cnt[all[i].index] = count;
	}
	return cnt;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {

	vector<int> cnt(points.size());
	for (size_t i = 0; i < points.size(); i++) {
		for (size_t j = 0; j < starts.size(); j++) {
			cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
		}
	}
	return cnt;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	vector<int> starts(n), ends(n);
	for (size_t i = 0; i < starts.size(); i++) {
		std::cin >> starts[i] >> ends[i];
	}
	vector<int> points(m);
	for (size_t i = 0; i < points.size(); i++) {
		std::cin >> points[i];
	}
	//use fast_count_segments
	vector<int> cnt = fast_count_segments(starts, ends, points);
	for (size_t i = 0; i < cnt.size(); i++) {
		std::cout << cnt[i] << ' ';
	}

	//while (true) {
	//	n = rand() % 10 + 5;
	//	m = rand() % 10 + 5;
	//	vector<int> starts(n);
	//	vector<int> ends(n);
	//	vector<int> points(m);
	//	for (int i = 0; i < n; i++) {
	//		starts[i] = rand() % 100 + 10;
	//		ends[i] = rand() % 100 + 10;
	//		if (starts[i] > ends[i])
	//			std::swap(starts[i], ends[i]);
	//		std::cout << starts[i] << ' ' << ends[i] << std::endl;
	//	}
	//	std::cout << std::endl;
	//	for (int i = 0; i < points.size(); i++) {
	//		points[i] = rand() % 100 + 10;
	//		std::cout << points[i] << ' ';
	//	}
	//	std::cout << std::endl;
	//	vector<int> v1 = naive_count_segments(starts, ends, points);
	//	vector<int> v2 = fast_count_segments(starts, ends, points);
	//	for (int i = 0; i < v1.size(); i++)
	//		std::cout << v1[i] << ' ';
	//	std::cout << std::endl;
	//	for (int i = 0; i < v2.size(); i++)
	//		std::cout << v2[i] << ' ';
	//	if (v1 != v2)
	//		break;
	//}
}
