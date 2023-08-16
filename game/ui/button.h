#pragma once

#include <functional>
#include "ui_element.h"

// UI Button
// Meant to be used in a menu
class Button : public UIElement
{
private:
	std::string text;
	Color color;

	Color highlight_color = Colors::Black;
	BackgroundColor highlight_color_bg = BackgroundColors::White;
	
	bool is_selected = false;

	std::function<void()> callback = nullptr;

public:
	Button(Point position, std::string text, Alignment alignment, Color color = Colors::White, std::function<void()> callback = nullptr);

	void SetHighlightColor(Color fg_color, BackgroundColor bg_color);

	bool IsSelected();
	void SetSelected(bool selected);

	void Draw(Surface& surface);

	void Callback();
};