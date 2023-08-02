#include "button.h"

Button::Button(Point position, std::string text, std::function<void()> callback, Color color)
	: UIElement(position, {}), text(text), callback(callback), color(color)
{}

void Button::Draw(Surface & surface)
{
	Color draw_color = color;
	if (is_selected)
		draw_color = Colors::Red;

	surface.Print(position.x, position.y, text, draw_color);
}
