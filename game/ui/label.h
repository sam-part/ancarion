#pragma once

#include <string>
#include "ui_element.h"
#include "../../engine/sdl/color.h"

class Label : public UIElement
{
private:
	std::string text;
	Color color;

public:
	Label(Point position, std::string text, Alignment alignment = {}, Color color = Colors::White);

	void Draw(Surface& surface);
};