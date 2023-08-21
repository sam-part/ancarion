#pragma once

#include "game_state.h"
#include "../game.h"
#include "../ui/ui.h"
#include "../util/ascii_art.h"

class MainMenu : public GameState
{
private:
	Surface surface;
	UI ui;

	AsciiArt art;

	Menu menu;

public:
	MainMenu(Game& game, Window& window);

	void RecenterSurface(Size window_size);

	void Update(Game& game, Input& input);
	void Draw(Window& window);
};