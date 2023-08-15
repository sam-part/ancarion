#include "menu.h"

Menu::Menu(MenuType menu_type)
	: UIElement({}, {}, {})
{
	SetMenuType(menu_type);
}

Menu::Menu(std::vector<Button> buttons, MenuType menu_type)
	: UIElement({}, {}, {}), buttons(buttons)
{
	SetMenuType(menu_type);
}

void Menu::SetMenuType(MenuType type)
{
	menu_type = type;

	if (menu_type == MenuType::Vertical)
	{
		move_back_action = Actions::General_MenuUp;
		move_forward_action = Actions::General_MenuDown;
	}
	else if (menu_type == MenuType::Horizontal)
	{
		move_back_action = Actions::General_MenuLeft;
		move_forward_action = Actions::General_MenuRight;
	}
}

void Menu::AddButton(Button button)
{
	buttons.push_back(button);
}

#include <iostream>
void Menu::Update(Input& input)
{
	if (input.ActionTriggered(move_back_action) && current_index > 0)
		current_index--;
	else if (input.ActionTriggered(move_forward_action) && current_index < buttons.size() - 1)
		current_index++;
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
