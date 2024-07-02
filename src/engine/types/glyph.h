#ifndef GLYPH_H
#define GLYPH_H

#include "color.h"

/*
 * Contains a character, foreground color, and background color
 * Represents a drawable ASCII character
 */
struct Glyph
{
 unsigned char character = ' ';

 Color color    {255, 255, 255};
 Color bg_color {0, 0, 0};
};

#endif //GLYPH_H