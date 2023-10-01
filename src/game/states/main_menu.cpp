#include "main_menu.h"

#include "../util/ascii_art.h"
#include "worldgen_menu.h"
#include <iostream>

MainMenu::MainMenu(Game& game, Window& window)
{
	auto quit = [&game]
	{
		game.Exit();
	};

	auto new_game = [&game]
	{
		StateManager& state_manager = game.GetStateManager();
		state_manager.PopState();
		state_manager.PushState(std::make_shared<WorldgenMenu>(game));
	};

	auto load_game = [&game]
	{
		//StateManager& state_manager = game.GetStateManager();
		//state_manager.PopState();
		// Load game
	};

	ui.Add(&menu);

	art.Open("data/art/main_menu.aa");
	Size art_size = art.GetSize();

	surface.SetDimensions(art_size.width, art_size.height);
	RecenterSurface(game.GetTerminalSize());

	art.Draw(surface);

	menu.AddButton(Button(Point(NULL, art_size.height - 9), "NEW WORLD", { AlignCenter }, new_game));
	menu.AddButton(Button(Point(NULL, art_size.height - 8), "LOAD GAME", { AlignCenter }, load_game));
	menu.AddButton(Button(Point(NULL, art_size.height - 7), "QUIT", { AlignCenter, -3 }, quit));

	surface.Print(1, art_size.height - 3, "Version 0.0.0d");
	surface.Print(1, art_size.height - 2, "Created by Sam Partington");

	SetBorder(surface, BorderStyle::Normal, Colors::White);
}

void MainMenu::RecenterSurface(Size window_size)
{
	Size art_size = art.GetSize();

	int origin_x = std::max((window_size.width - art_size.width) / 2, 0);
	int origin_y = std::max((window_size.height - art_size.height) / 2, 0);

	surface.SetOrigin(origin_x, origin_y);
}

void MainMenu::Update(Game& game, Input& input)
{
	ui.Update(input);

	if (input.WindowResized())
		RecenterSurface(game.GetTerminalSize());
}

void MainMenu::Draw(Window& window)
{
	ui.Draw(surface);
	window.DrawSurface(surface);
}
