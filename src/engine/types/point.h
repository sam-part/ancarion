#pragma once

#include <vector>

struct Point
{
	int x, y;

	Point();
	Point(int x, int y);

	friend bool operator==(const Point& lhs, const Point& rhs);
	friend Point operator+(const Point& lhs, const Point& rhs);
};

extern const std::vector<Point> directions;