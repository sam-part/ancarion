#include "label.h"

Label::Label(Point position, std::string text, Alignment alignment, Color color)
	: UIElement(position, {}, alignment), text(text), color(color)
{}

void Label::Draw(Surface& surface)
{
	surface.PrintAligned(position.x, position.y, text, alignment, color);
}
