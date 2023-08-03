#include "menu.h"

Menu::Menu()
	: UIElement({}, {}, {})
{}

Menu::Menu(std::vector<Button> buttons)
	: UIElement({}, {}, {}), buttons(buttons)
{}

void Menu::AddButton(Button button)
{
	buttons.push_back(button);
}

void Menu::Update()
{
}

void Menu::Draw(Surface& surface)
{
	int index = 0;
	for (Button& button : buttons)
	{
		button.SetSelected(index == current_index);
		button.Draw(surface);
		index++;
	}
}
