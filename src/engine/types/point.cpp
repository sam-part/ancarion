#include "point.h"

bool operator==(const Point& lhs, const Point& rhs)
{
    return lhs.x == rhs.x;
}

Point operator+(const Point& lhs, const Point& rhs)
{
    return Point(lhs.x + rhs.x, lhs.y + rhs.y);
}

Point::Point()
    : x(0), y(0)
{}

Point::Point(int x, int y)
    : x(x), y(y)
{}

const std::vector<Point> directions = {
    Point(1, 0),
    Point(-1, 0),
    Point(0, 1),
    Point(0, -1)
};