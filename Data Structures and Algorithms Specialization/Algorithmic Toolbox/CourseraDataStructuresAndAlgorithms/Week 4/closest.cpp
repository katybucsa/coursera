#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <limits.h>

using std::vector;
using std::string;
using std::pair;
using std::min;


class Point {
public:
	int x;
	int y;
	Point(int x, int y) :x{ x }, y{ y }{}
	Point() : x{ 0 }, y{ 0 }{}
};

double minimal_distance(vector<Point> pointsX, vector<Point> pointsY, int left, int right) {

	if (right == left + 1)
		return double(std::sqrt(std::pow(pointsX[left].x - pointsX[right].x, 2) + std::pow(pointsX[left].y - pointsX[right].y, 2)));
	if (left == right)
		return INT_MAX;
	int middle = left + (right - left) / 2;
	vector<Point> pointsYL, pointsYR;
	for (int i = 0; i < pointsY.size(); i++) {
		if (pointsY[i].x <= pointsX[middle].x && pointsYL.size() < middle - left + 1) {
			pointsYL.push_back(pointsY[i]);
		}
		else {
			pointsYR.push_back(pointsY[i]);
		}
	}
	double d1 = minimal_distance(pointsX, pointsYL, left, middle);
	double d2 = minimal_distance(pointsX, pointsYR, middle + 1, right);
	double d = std::min(d1, d2);
	vector<Point> remaining;
	for (int i = 0; i < pointsY.size(); i++) {
		if (std::abs(pointsY[i].x - pointsX[middle].x) < d)
			remaining.push_back(pointsY[i]);
	}
	double dist = INT_MAX;
	int s = remaining.size() - 1;
	for (int i = 0; i < s; i++) {
		for (int j = i + 1; j < remaining.size() && remaining[j].y - remaining[i].y < d; j++) {
			double d = double(std::sqrt(std::pow(remaining[i].x - remaining[j].x, 2) + std::pow(remaining[i].y - remaining[j].y, 2)));
			if (d < dist)
				dist = d;
		}
	}
	return std::min(d, dist);
}

int main() {
	size_t n;
	std::cin >> n;
	vector<int> x(n);
	vector<int> y(n);
	vector<Point> pointsX(n);
	vector<Point> pointsY(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> pointsX[i].x >> pointsX[i].y;
		pointsY[i].x = pointsX[i].x;
		pointsY[i].y = pointsX[i].y;
	}
	std::sort(pointsX.begin(), pointsX.end(), [](Point p1, Point p2) {return p1.x < p2.x; });
	std::sort(pointsY.begin(), pointsY.end(), [](Point p1, Point p2) {return p1.y < p2.y; });
	std::cout << std::fixed;
	std::cout << std::setprecision(9) << minimal_distance(pointsX, pointsY, 0, pointsX.size() - 1) << "\n";
}
