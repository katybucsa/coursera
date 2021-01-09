#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
	int start, end;
};

vector<int> optimal_points(vector<Segment>& segments) {

	vector<int> points;
	int poz = 0;
	while (poz < segments.size()) {
		int current_poz = poz;
		while (poz<segments.size() && segments[poz].start <= segments[current_poz].end && segments[poz].end >= segments[current_poz].end)
		{
			poz++;
		}
		points.push_back(segments[current_poz].end);
	}

	return points;
}

int main() {
	int n;
	std::cin >> n;
	vector<Segment> segments(n);
	for (size_t i = 0; i < segments.size(); ++i) {
		std::cin >> segments[i].start >> segments[i].end;
	}

	std::sort(segments.begin(), segments.end(), [](Segment s1, Segment s2) {return s1.end < s2.end; });
	vector<int> points = optimal_points(segments);
	std::cout << points.size() << "\n";
	for (size_t i = 0; i < points.size(); ++i) {
		std::cout << points[i] << " ";
	}
}
