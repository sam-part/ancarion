#include "worldgen_menu.h"
#include <iostream>

void WorldgenMenu::GenerateWorld()
{
	//std::thread worldgen_thread(&WorldGenerator::Generate, &worldgen);
	//worldgen_thread.detach();

	worldgen.Generate();
	world = worldgen.GetWorld();

	Size world_size = world.GetSize();
	Size display_size = Size{ world_display_surface.GetWidth(), world_display_surface.GetHeight() };

	for (int x = 0; x < world_size.width; x++)
	{
		for (int y = 0; y < world_size.height; y++)
		{
			if (!display_size.InBounds(x, y))
				continue;

			Glyph glyph;

			glyph.character = '~';
			glyph.color = { 0, 0, 255 };

			const ChunkInfo& chunk = world.GetChunk(x, y);
			if (chunk.elevation > 0.25)
			{
				glyph.character = '#';
				glyph.color = { 0, 255, 0 };
			}

			world_display_surface.Set(x, y, glyph);
		}
	}
}

WorldgenMenu::WorldgenMenu(Game& game)
{
	Size terminal_size = game.GetTerminalSize();

	world_display_surface.SetDimensions(terminal_size.width, terminal_size.height);
	world_display_surface.SetOrigin(0, 0);

	GenerateWorld();
}

void WorldgenMenu::Update(Game& game, Input& input)
{
	if (input.ActionTriggered(Actions::Worldgen_Regenerate))
	{
		GenerateWorld();
	}
}

void WorldgenMenu::Draw(Window& window)
{
	window.DrawSurface(world_display_surface);
}