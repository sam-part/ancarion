#pragma once

#include <vector>
#include <string>
#include "glyph.h"
#include "../types/alignment.h"

// 2D container of character
// Internal structure used in a Surface
struct SurfaceData
{
	int origin_x = 0;
	int origin_y = 0;
	int width = 0;
	int height = 0;
	
	std::vector<Glyph> data {};
};

// A class to represent 2D container of characters
// All terminal graphics are drawn through surface objects
class Surface
{
private:
	SurfaceData surface_data {};

	bool InBounds(int x, int y);
	int GetIndex_2D(int x, int y);

public:
	Surface();
	Surface(int origin_x, int origin_y, int width, int height);

	void SetOrigin(int x, int y);
	void SetDimensions(int width, int height);

	void Set(int x, int y, unsigned char character, Color color = Colors::White, Color bg_color = Colors::Black);
	void Set(int x, int y, Glyph glyph);

	void SetColor(int x, int y, Color color, Color bg_color = Colors::Black);
	void SetBackgroundColor(int x, int y, Color color);

	void Print(int x, int y, const std::string& text, Color color = Colors::White, Color bg_color = Colors::Black);

	// Prints text aligned to the surface's bounds
	void PrintAligned(int x, int y, const std::string& text, Alignment alignment, Color color = Colors::White, Color bg_color = Colors::Black);

	void Clear();

	int GetWidth() const;
	int GetHeight() const;

	const SurfaceData& GetData() const;
};