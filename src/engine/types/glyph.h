#ifndef GLYPH_H
#define GLYPH_H

#include "color.h"

using Character = char8_t;

/*
 * Contains a character, foreground color, and background color
 * Represents a drawable ASCII character
 */
struct Glyph
{
 Character character = ' ';

 Color color    {255, 255, 255};
 Color bg_color {0, 0, 0};
};

#endif //GLYPH_H