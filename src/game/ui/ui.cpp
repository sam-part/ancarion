#include "ui.h"

void UI::Update(Input& input)
{
	for (UIElement* ui_element : ui_elements)
	{
		ui_element->Update(input);
	}
}

void UI::Draw(Surface& surface)
{
	for (UIElement* ui_element : ui_elements)
	{
		ui_element->Draw(surface);
	}
}

void UI::Add(UIElement* ui_element)
{
	ui_elements.push_back(std::move(ui_element));
}

void UI::Clear()
{
	ui_elements.clear();
}
