#pragma once

#include <vector>
#include <memory>

#include "ui_element.h"
#include "border.h"
#include "label.h"
#include "button.h"
#include "menu.h"

class UI
{
private:
	std::vector<std::unique_ptr<UIElement>> ui_elements;
	
public:
	void HandleInput();
	void Draw(Surface& surface);

	void Add(std::unique_ptr<UIElement> ui_element);
	void Clear();
};