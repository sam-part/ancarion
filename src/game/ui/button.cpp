#include "button.h"

Button::Button(Point position, std::string text, Alignment alignment, Color color, std::function<void()> callback)
	: UIElement(position, {}, alignment), text(text), color(color), callback(callback)
{}

Button::Button(Point position, std::string text, Alignment alignment, std::function<void()> callback)
	: UIElement(position, {}, alignment), text(text), callback(callback)
{}

void Button::SetHighlightColor(Color fg_color, BackgroundColor bg_color)
{
	highlight_color = fg_color;
	highlight_color_bg = bg_color;
}

bool Button::IsSelected()
{
	return is_selected;
}

void Button::SetSelected(bool selected)
{
	is_selected = selected;
}

void Button::Draw(Surface & surface)
{
	if (is_selected)
		surface.PrintAligned(position.x, position.y, text, alignment, highlight_color, highlight_color_bg);
	else
		surface.PrintAligned(position.x, position.y, text, alignment, color);
}

void Button::Callback()
{
	if (callback)
		callback();
}
