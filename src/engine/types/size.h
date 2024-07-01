//
// Created by sam on 01/07/24.
//

#ifndef SIZE_H
#define SIZE_H

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
 size_t getIndex(int x, int y) const;

 // Determines if a point lies within the object's bounds
 bool inBounds(int x, int y) const;
};

#endif //SIZE_H
