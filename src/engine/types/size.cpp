#include "size.h"

Size::Size()
	: width(0), height(0)
{}

Size::Size(int width, int height)
	: width(width), height(height)
{}

int Size::GetIndex_2D(int x, int y)
{
	return y * width + x;
}

bool Size::InBounds(int x, int y)
{
	return (x >= 0 && y >= 0 && x < width && y < height);
}
