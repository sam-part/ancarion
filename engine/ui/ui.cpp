#include "ui.h"

void UI::Draw(Surface& surface)
{
	for (std::unique_ptr<UIElement>& ui_element : ui_elements)
	{
		ui_element->Draw(surface);
	}
}

void UI::Add(std::unique_ptr<UIElement> ui_element)
{
	ui_elements.push_back(std::move(ui_element));
}

void UI::Clear()
{
	ui_elements.clear();
}
