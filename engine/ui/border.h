#pragma once

#include "../types/characters.h"
#include "../types/rect.h"
#include "../sdl/color.h"
#include "../sdl/surface.h"

namespace BorderStyle
{
	struct BorderStyle
	{
		unsigned char vertical_line;
		unsigned char horizontal_line;
		unsigned char tl_corner;
		unsigned char tr_corner;
		unsigned char bl_corner;
		unsigned char br_corner;
	};

	extern BorderStyle Normal;
	extern BorderStyle Double;
	extern BorderStyle Solid;
	extern BorderStyle None;
}

void SetBorder(Surface& surface, BorderStyle::BorderStyle border_style, Color color);
void SetBorder(Surface& surface, Rect rect, BorderStyle::BorderStyle border_style, Color color);