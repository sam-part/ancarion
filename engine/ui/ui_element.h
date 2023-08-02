#pragma once

#include "../sdl/surface.h"
#include "../types/point.h"
#include "../types/size.h"

class UIElement
{
protected:
	Point position{};
	Size size{};

public:
	UIElement(Point position, Size size)
		: position(position), size(size)
	{}

	virtual void Draw(Surface& surface) = 0;
};