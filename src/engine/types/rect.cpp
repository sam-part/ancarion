#include "rect.h"

Rect::Rect()
	: origin(Point(0, 0)), size(Size(0, 0))
{}

Rect::Rect(Point origin, Size size)
	: origin(origin), size(size)
{}

bool Rect::InBounds(int x, int y)
{
	return size.InBounds(x - origin.x, y - origin.y);
}
