#include "surface.h"

bool Surface::InBounds(int x, int y)
{
	return (x >= 0 && y >= 0 && x < surface_data.width && y < surface_data.height);
}

int Surface::GetIndex_2D(int x, int y)
{
	return y * surface_data.width + x;
}

Surface::Surface(int origin_x, int origin_y, unsigned int width, unsigned int height)
{
	surface_data = SurfaceData{ origin_x, origin_y, width, height };
	surface_data.data.resize(width * height);
}

void Surface::SetOrigin(int x, int y)
{
	surface_data.origin_x = x;
	surface_data.origin_y = y;
}

void Surface::SetDimensions(unsigned int width, unsigned int height)
{
	surface_data.width = width;
	surface_data.height = height;

	surface_data.data.clear();
	surface_data.data.resize(width * height);
}

unsigned int Surface::GetWidth() const
{
	return surface_data.width;
}

unsigned int Surface::GetHeight() const
{ 
	return surface_data.height;
}

void Surface::Set(int x, int y, unsigned char character, Color color, BackgroundColor bg_color)
{
	if (!InBounds(x, y))
		return;

	int idx = GetIndex_2D(x, y);

	surface_data.data[idx].character = character;
	surface_data.data[idx].color = color;
	surface_data.data[idx].bg_color = bg_color;
}

void Surface::Set(int x, int y, Glyph glyph)
{
	if (!InBounds(x, y))
		return;

	surface_data.data[GetIndex_2D(x, y)] = glyph;
}

void Surface::SetColor(int x, int y, Color color)
{
	if (!InBounds(x, y))
		return;

	surface_data.data[GetIndex_2D(x, y)].color = color;
}

void Surface::SetBackgroundColor(int x, int y, BackgroundColor bg_color)
{
	if (!InBounds(x, y))
		return;

	surface_data.data[GetIndex_2D(x, y)].bg_color = bg_color;
}

void Surface::Print(int x, int y, const std::string& text, Color color, BackgroundColor bg_color)
{
	if (!InBounds(x, y))
		return;

	int idx = GetIndex_2D(x, y);
	int print_length = text.length();

	// If part of text is out of range, reduce print length up to that point (ignores out of range text)
	if (x + print_length > surface_data.width)
	{
		print_length -= (x + print_length - surface_data.width);
	}

	for (int i = 0; i < print_length; i++)
	{
		surface_data.data[idx + i].character = text[i];
		surface_data.data[idx + i].color = color;
		surface_data.data[idx + i].bg_color = bg_color;
	}
}

void Surface::Clear()
{
	Glyph empty_glyph{};
	std::fill(surface_data.data.begin(), surface_data.data.end(), empty_glyph);
}

const SurfaceData& Surface::GetData() const
{
	return surface_data;
}
