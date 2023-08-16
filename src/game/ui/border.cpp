#include "border.h"

namespace BorderStyle
{
	BorderStyle Normal
	{
		Characters::VerticalLine,
		Characters::HorizontalLine,
		Characters::TLCorner,
		Characters::TRCorner,
		Characters::BLCorner,
		Characters::BRCorner,
	};

	BorderStyle Double
	{
		Characters::DoubleVerticalLine,
		Characters::DoubleHorizontalLine,
		Characters::DoubleTLCorner,
		Characters::DoubleTRCorner,
		Characters::DoubleBLCorner,
		Characters::DoubleBRCorner,
	};

	BorderStyle Solid
	{
		Characters::Solid,
		Characters::Solid,
		Characters::Solid,
		Characters::Solid,
		Characters::Solid,
		Characters::Solid
	};

	BorderStyle None
	{
		' ',
		' ',
		' ',
		' ',
		' ',
		' '
	};
};

void SetBorder(Surface& surface, BorderStyle::BorderStyle border_style, Color color)
{
	unsigned const int width = surface.GetWidth();
	unsigned const int height = surface.GetHeight();

	for (int x = 1; x < width - 1; x++)
	{
		surface.Set(x, 0, border_style.horizontal_line, color);
		surface.Set(x, height - 1, border_style.horizontal_line, color);
	}

	for (int y = 1; y < height - 1; y++)
	{
		surface.Set(0, y, border_style.vertical_line, color);
		surface.Set(width - 1, y, border_style.vertical_line, color);
	}

	surface.Set(0, 0, border_style.tl_corner, color);
	surface.Set(width - 1, 0, border_style.tr_corner, color);
	surface.Set(0, height - 1, border_style.bl_corner, color);
	surface.Set(width - 1, height - 1, border_style.br_corner, color);
}

void SetBorder(Surface& surface, Rect rect, BorderStyle::BorderStyle border_style, Color color)
{
	for (int x = rect.origin.x + 1; x < rect.origin.x + rect.size.width - 1; x++)
	{
		surface.Set(x, rect.origin.y, border_style.horizontal_line, color);
		surface.Set(x, rect.origin.y + rect.size.height - 1, border_style.horizontal_line, color);
	}

	for (int y = rect.origin.y + 1; y < rect.origin.y + rect.size.height - 1; y++)
	{
		surface.Set(rect.origin.x, y, border_style.vertical_line, color);
		surface.Set(rect.origin.x + rect.size.width - 1, y, border_style.vertical_line, color);
	}

	surface.Set(rect.origin.x, rect.origin.y, border_style.tl_corner, color);
	surface.Set(rect.origin.x + rect.size.width - 1, rect.origin.y, border_style.tr_corner, color);
	surface.Set(rect.origin.x, rect.origin.y + rect.size.height - 1, border_style.bl_corner, color);
	surface.Set(rect.origin.x + rect.size.width - 1, rect.origin.y + rect.size.height - 1, border_style.br_corner, color);
}
