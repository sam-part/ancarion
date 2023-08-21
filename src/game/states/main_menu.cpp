#include "main_menu.h"

#include "../util/ascii_art.h"
#include <iostream>

MainMenu::MainMenu(Game& game, Window& window)
{
	int window_width = window.GetTerminalWidth();
	int window_height = window.GetTerminalHeight();

	auto quit = [&game]
	{
		game.Exit();
	};

	auto new_game = [&game]
	{
		StateManager& state_manager = game.GetStateManager();
		state_manager.PopState();
		//state_manager.PushState(std::make_shared<Worldgen>(game, window));
	};

	auto load_game = [&game]
	{
		//StateManager& state_manager = game.GetStateManager();
		//state_manager.PopState();
		// Load game
	};

	ui.Add(&menu);

	AsciiArt art("data/art/main_menu.aa");
	Size art_size = art.GetSize();

	surface.SetDimensions(art_size.width, art_size.height);
	if (window_width > art_size.width || window_height > art_size.height)
		surface.SetOrigin((window_width - art_size.width) / 2, (window_height - art_size.height) / 2);

	art.Draw(surface);

	menu.AddButton(Button(Point(NULL, art_size.height - 9), "NEW WORLD", { AlignCenter }, new_game));
	menu.AddButton(Button(Point(NULL, art_size.height - 8), "LOAD GAME", { AlignCenter }, load_game));
	menu.AddButton(Button(Point(NULL, art_size.height - 7), "QUIT", { AlignCenter, -3 }, quit));

	surface.Print(1, art_size.height - 3, "Version 0.0.0d");
	surface.Print(1, art_size.height - 2, "Created by Sam Partington");

	SetBorder(surface, BorderStyle::Normal, Colors::White);
}

void MainMenu::Update(Game& game, Input& input)
{
	ui.Update(input);
}

void MainMenu::Draw(Window& window)
{
	ui.Draw(surface);
	window.DrawSurface(surface);
}
