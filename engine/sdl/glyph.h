#pragma once

#include "color.h"

struct Glyph
{
	unsigned char character = ' ';
	Color color{ 0,0,0 };
	BackgroundColor bg_color = BackgroundColors::None;
};