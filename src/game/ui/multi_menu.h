#pragma once

#include "ui_element.h"
#include "menu.h"
#include <vector>

class MultiMenu
{
private:
	std::vector<Menu> menus;

	bool is_active = true;
	unsigned int current_menu_index = 0;

	MenuType menu_type = MenuType::Vertical;

	ActionID move_prev_menu_action;
	ActionID move_next_menu_action;
};