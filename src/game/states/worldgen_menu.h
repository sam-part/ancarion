#pragma once

#include "game_state.h"
#include "../game.h"
#include "../ui/ui.h"
#include "../world/world.h"
#include "../world/world_generator.h"

#include <thread>

// This menu will display world generation parameters to the player
// For now, it will just display the world after it is generated

class WorldgenMenu : public GameState
{
private:
	Surface world_display_surface;
	Surface ui_surface;
	UI ui;

	WorldGenerator worldgen;
	//World world;

	void GenerateWorld();

public:
	WorldgenMenu();

	void Update(Game& game, Input& input);
	void Draw(Window& window);
};