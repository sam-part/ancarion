#pragma once

#include "../../engine/types/characters.h"
#include "../../engine/types/rect.h"
#include "../../engine/sdl/color.h"
#include "../../engine/sdl/surface.h"

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