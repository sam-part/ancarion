#pragma once

#include "../../engine/sdl/surface.h"
#include "../../engine/sdl/input.h"
#include "../../engine/types/point.h"
#include "../../engine/types/size.h"
#include "../actions.h"

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
	virtual void Update(Input& input) {};
};