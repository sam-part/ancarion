#pragma once

struct Size
{
	int width, height;

	Size();
	Size(int width, int height);

	// Returns the 2D index of a point (ordered row, column)
	// Bounds checking should be performed before
	int GetIndex_2D(int x, int y);

	// Checks whether or not a point is within the bounds of the size's width and height
	bool InBounds(int x, int y);
};