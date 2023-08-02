#include "game.h"

Game::Game()
	: game_config(config_path)
{
	WindowSettings window_settings;
	window_settings.window_name = "Ancarion";
	window_settings.terminal_width = game_config.Get<int>("window", "terminal_width");
	window_settings.terminal_height = game_config.Get<int>("window", "terminal_height");
	window_settings.font_path = game_config.GetString("window", "font");
	window_settings.is_window_resizable = game_config.Get<bool>("window", "resizable");

	window.CreateWindow(window_settings);
}

void Game::Run()
{
	game_running = true;

	Surface surface(0, 0, window.GetTerminalWidth(), window.GetTerminalHeight());
	SetBorder(surface, BorderStyle::Double, Colors::White);

	UI ui;

	Label label(Point(1, 1), "Label");
	ui.Add(std::make_unique<Label>(label));

	ui.Draw(surface);

	
	Glyph g;
	g.character = 'A';
	g.color = Colors::Red;
	g.bg_color = BackgroundColors::DarkGrey;
	surface.Set(5, 5, g);

	surface.Print(1, 10, "Hello, highlighted text", Colors::Black, BackgroundColors::White);

	while (game_running && window.IsOpen())
	{
		window.Clear();
		window.PollEvents();

		window.DrawSurface(surface);

		window.DisplayTerminal();
	}
}
