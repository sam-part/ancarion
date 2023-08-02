#include "label.h"

Label::Label(Point position, std::string text, Color color)
	: UIElement(position, {}), text(text), color(color)
{}

void Label::Draw(Surface& surface)
{
	surface.Print(position.x, position.y, text, color);
}
