#include "ascii_art.h"

#include "compression.h"

AsciiArt::AsciiArt(const std::string& file_path)
{
	Open(file_path);
}

void AsciiArt::Open(const std::string& file_path)
{
	std::string art_raw = Gzip::ReadFile(file_path);

	width = static_cast<IntType>(art_raw[0]);
	height = static_cast<IntType>(art_raw[1]);

	data.resize(width * height);

	int index = 0;
	int position = 2;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Glyph glyph;
			
			glyph.character = static_cast<IntType>(art_raw[position++]);
			glyph.color = Color {
				static_cast<IntType>(art_raw[position++]),
				static_cast<IntType>(art_raw[position++]),
				static_cast<IntType>(art_raw[position++])
			};
			glyph.bg_color = Color {
				static_cast<IntType>(art_raw[position++]),
				static_cast<IntType>(art_raw[position++]),
				static_cast<IntType>(art_raw[position++])
			};

			data[index] = glyph;
			index++;
		}
	}
}

void AsciiArt::Draw(Surface& surface, Point position)
{
	int index = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			surface.Set(x + position.x, y + position.y, data[index]);

			index++;
		}
	}
}

Size AsciiArt::GetSize() const
{
	return Size{ width, height };
}
