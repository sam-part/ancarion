#pragma once

#include "../../engine/sdl/surface.h"
#include "../../engine/types/size.h"
#include "../../engine/types/point.h"
#include <vector>
#include <string>

class AsciiArt
{
private:
	using IntType = uint8_t;

	std::vector<Glyph> data {};
	IntType width = 0;
	IntType height = 0;

public:
	AsciiArt() = default;
	AsciiArt(const std::string& file_path);

	void Open(const std::string& file_path);
	void Draw(Surface& surface, Point position = {0, 0});

	Size GetSize() const;
}; 