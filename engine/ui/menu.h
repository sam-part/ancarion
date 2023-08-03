#pragma once

#include "ui_element.h"
#include "button.h"
#include <vector>

class Menu : public UIElement
{
private:
	std::vector<Button> buttons = {};
	int current_index = 0;
	bool selection_made = false;

public:
	Menu();
	Menu(std::vector<Button> buttons);

	void AddButton(Button button);

	void Update();

	void Draw(Surface& surface);

	bool SelectionMade();
	int GetSelectedIndex();
};