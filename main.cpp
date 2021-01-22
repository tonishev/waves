#include <array>
#include <iostream>
#include <queue>
#include <set>



struct Point {

	int x{ 0 };
	int y{ 0 };

	friend bool operator<(const Point& a, const Point& b) {

		return a.x < b.x || (a.x == b.x && a.y < b.y);

	}

};

std::size_t getDigitSum(int number) {

	if (number < 0)
		number = number * -1;

	std::size_t sum = 0;

	while (number > 0) {

		sum = sum + (number % 10);
		number = number / 10;

	}

	return sum;

}

bool isValidPoint(const Point& point) {

	const std::size_t CONDITION = 25;
	return (getDigitSum(point.x) + getDigitSum(point.y)) <= CONDITION;

}

bool isVisitedPoint(const std::set<Point>& visited, const Point& point) {

	return visited.find(point) != visited.end();

}

std::array<Point, 4> expand(const Point& point) {

	std::array<Point, 4> arr;

	arr[0] = { point.x, point.y - 1 };
	arr[1] = { point.x, point.y + 1 };
	arr[2] = { point.x - 1, point.y };
	arr[3] = { point.x + 1, point.y };

	return arr;

}

int main() {

	const Point startPoint{ 1000, 1000 };

	std::queue<Point> unverified;
	unverified.push(startPoint);
	std::set<Point> visited{ startPoint };
	
	std::size_t cValidPoints = 0;

	while (!unverified.empty()) {

		auto current = unverified.front();

		if (isValidPoint(current)) {

			++cValidPoints;

			for (const auto& child : expand(current)) {

				if (!isVisitedPoint(visited, child)) {

					visited.insert(child);
					unverified.push(child);

				}

			}

		}

		unverified.pop();

	}

	std::cout << cValidPoints << '\n';

	return 0;

}