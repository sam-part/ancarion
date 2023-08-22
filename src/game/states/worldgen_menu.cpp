#include "worldgen_menu.h"
#include <iostream>

void WorldgenMenu::GenerateWorld()
{
	std::thread worldgen_thread(&WorldGenerator::Generate, &worldgen);
	worldgen_thread.detach();
}

WorldgenMenu::WorldgenMenu()
{
	GenerateWorld();
}

void WorldgenMenu::Update(Game& game, Input& input)
{
	if (worldgen.StageChanged())
		std::cout << worldgen.GetCurrentStage().message << " (" << worldgen.GetCurrentStage().percent_finished << "%)\n";
}

void WorldgenMenu::Draw(Window& window)
{
}
