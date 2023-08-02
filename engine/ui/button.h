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
	
	bool is_selected;
	std::function<void()> callback;

public:
	Button(Point position, std::string text, std::function<void()> callback = nullptr, Color color = Colors::White);

	void Draw(Surface& surface);
};