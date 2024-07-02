#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

/*
 * Contains a 32-bit RGBA color
 */
struct Color
{
 uint8_t r    {};
 uint8_t g    {};
 uint8_t b    {};
 uint8_t a {255};
};

#endif //COLOR_H
