#include "main_menu.h"

#include "../util/ascii_art.h"
#include <iostream>

MainMenu::MainMenu(Game& game, Window& window)
{
	int width = window.GetTerminalWidth();
	int height = window.GetTerminalHeight();

	surface.SetDimensions(width, height);

	int center_y = height / 2;

	auto quit = [&]
	{
		game.Exit();
	};

	menu.AddButton(Button(Point(NULL, height - 9), "NEW WORLD", {AlignCenter}));
	menu.AddButton(Button(Point(NULL, height - 8), "LOAD GAME", { AlignCenter }));
	menu.AddButton(Button(Point(NULL, height - 7), "QUIT", { AlignCenter, -3}, quit));

	ui.Add(&menu);

	AsciiArt art("data/art/main_menu.aa");
	art.Draw(surface);

	surface.Print(1, height - 3, "Version 0.0.0d");
	surface.Print(1, height - 2, "Created by Sam Partington");

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
