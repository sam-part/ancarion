#pragma once

#include "ui_element.h"
#include "button.h"
#include <vector>

enum class MenuType
{
	Vertical,
	Horizontal
};

class Menu : public UIElement
{
private:
	std::vector<Button> buttons = {};

	bool is_active = true;
	unsigned int current_index = 0;
	bool selection_made = false;

	MenuType menu_type = MenuType::Vertical;

	ActionID move_back_action;
	ActionID move_forward_action;

public:
	Menu(MenuType menu_type = MenuType::Vertical);
	Menu(std::vector<Button> buttons, MenuType menu_type = MenuType::Vertical);

	void SetActive(bool active);
	bool IsActive() const;

	void SetMenuType(MenuType type);
	void AddButton(Button button);

	void Update(Input& input);

	void Draw(Surface& surface);

	bool SelectionMade() const;
	int GetSelectedIndex() const;
};