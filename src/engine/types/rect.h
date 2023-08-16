#pragma once

#include "point.h"
#include "size.h"

struct Rect
{
	Point origin;
	Size size;

	Rect();
	Rect(Point origin, Size size);

	bool InBounds(int x, int y);
};