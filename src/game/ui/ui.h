#pragma once

#include <vector>

#include "../../engine/sdl/input.h"
#include "ui_element.h"
#include "border.h"
#include "label.h"
#include "button.h"
#include "menu.h"

class UI
{
private:
	std::vector<UIElement*> ui_elements;
	
public:
	void Update(Input& input);
	void Draw(Surface& surface);

	void Add(UIElement* ui_element);
	void Clear();
};