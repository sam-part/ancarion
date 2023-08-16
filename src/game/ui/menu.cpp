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

void Menu::SetActive(bool active)
{
	is_active = active;
}

bool Menu::IsActive() const
{
	return is_active;
}

void Menu::AddButton(Button button)
{
	buttons.push_back(button);
}

void Menu::Update(Input& input)
{
	if (!is_active)
		return;

	if (selection_made)
	{
		is_active = false;
		return;
	}

	if (input.ActionTriggered(move_back_action) && current_index > 0)
	{
		current_index--;
		selection_made = false;
	}
	else if (input.ActionTriggered(move_forward_action) && current_index < buttons.size() - 1)
	{
		current_index++;
		selection_made = false;
	}
	
	if (input.ActionTriggered(Actions::General_Continue))
	{
		buttons[current_index].Callback();
		selection_made = true;
	}
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

bool Menu::SelectionMade() const
{
	return selection_made && is_active;
}

int Menu::GetSelectedIndex() const
{
	return current_index;
}
