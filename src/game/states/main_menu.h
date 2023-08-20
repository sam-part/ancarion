#pragma once

#include "game_state.h"
#include "../game.h"
#include "../ui/ui.h"

class MainMenu : public GameState
{
private:
	Surface surface;
	UI ui;

	Menu menu;

public:
	MainMenu(Game& game, Window& window);

	void change() { surface.Set(0, 0, 'a'); };

	void Update(Game& game, Input& input);
	void Draw(Window& window);
};