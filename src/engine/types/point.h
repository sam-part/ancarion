#pragma once

struct Point
{
	int x, y;

	Point();
	Point(int x, int y);

	friend bool operator==(const Point& lhs, const Point& rhs);
	friend Point operator+(const Point& lhs, const Point& rhs);
};