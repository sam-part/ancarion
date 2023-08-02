#pragma once

#include <string>
#include "ui_element.h"
#include "../sdl/color.h"

/*

TextAlignment

*/

class Label : public UIElement
{
private:
	std::string text;
	Color color;

public:
	Label(Point position, std::string text, Color color = Colors::White);

	void Draw(Surface& surface);
};