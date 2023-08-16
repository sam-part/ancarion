#include "ui.h"

void UI::Update(Input& input)
{
	for (size_t index = 0; index < ui_elements.size(); index++)
	{
		UIElement* ui_element = ui_elements[index];

		if (ui_element == nullptr) // Remove potentially invalid UI elements
		{
			ui_elements.erase(ui_elements.begin() + index);
			continue;
		}

		ui_element->Update(input);
	}
}

void UI::Draw(Surface& surface)
{
	for (UIElement* ui_element : ui_elements)
	{
		if (ui_element != nullptr)
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
