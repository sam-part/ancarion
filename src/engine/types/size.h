//
// Created by sam on 01/07/24.
//

#ifndef SIZE_H
#define SIZE_H

#include "point.h"

/*
 * Represents a 2D size
 */
struct Size
{
 int width  {};
 int height {};

 Size() = default;
 Size(int width, int height);

 // Calculates the 1D index of a 2D point
 // Bounds checking should be performed beforehand
 size_t get_index(int x, int y) const;

 // Determines if a point lies within the object's bounds
 bool in_bounds(int x, int y) const;
 bool in_bounds(Point2D point) const;
};

#endif //SIZE_H
