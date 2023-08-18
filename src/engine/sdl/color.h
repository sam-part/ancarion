#pragma once

#include <cstdint>
#include <vector>

struct Color
{
	uint8_t r, g, b;
};

namespace Colors
{
	extern Color White;
	extern Color Black;

	extern Color Red;
	extern Color Green;
	extern Color Blue;
	extern Color Yellow;
	extern Color Magenta;
	extern Color Cyan;
	extern Color Grey;

	extern Color DarkRed;
	extern Color DarkGreen;
	extern Color DarkBlue;
	extern Color DarkYellow;
	extern Color DarkMagenta;
	extern Color DarkCyan;
	extern Color DarkGrey;
}