//
// Created by sam on 01/07/24.
//

#include "size.h"

Size::Size(int width, int height)
    : width(width), height(height)
{}

size_t Size::get_index(int x, int y) const
{
    return y * width + x;
}

bool Size::in_bounds(int x, int y) const
{
    return (x >= 0 &&
            y >= 0 &&
            x < width &&
            y < height);
}

bool Size::in_bounds(Point2D point) const
{
    return in_bounds(point.x, point.y);
}
