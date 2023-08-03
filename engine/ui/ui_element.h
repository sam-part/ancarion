#pragma once

#include "../sdl/surface.h"
#include "../types/point.h"
#include "../types/size.h"

class UIElement
{
protected:
	Point position{};
	Size size{};
	Alignment alignment{};

public:
	UIElement(Point position, Size size, Alignment alignment)
		: position(position), size(size), alignment(alignment)
	{}

	virtual void Draw(Surface& surface) = 0;
};