#pragma once

#include "color.h"

struct Glyph
{
	unsigned char character = ' ';
	Color color{ 255, 255, 255 };
	Color bg_color{ 0, 0, 0 };
};