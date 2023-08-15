#include "game.h"
#include <chrono>

Game::Game()
	: game_config(config_path)
{
	if (game_config.HasErrors())
		return;

	WindowSettings window_settings;
	window_settings.window_name = "Ancarion";
	window_settings.terminal_width = game_config.Get<int>("window", "terminal_width");
	window_settings.terminal_height = game_config.Get<int>("window", "terminal_height");
	window_settings.min_terminal_width = 60;
	window_settings.min_terminal_height = 34;
	window_settings.font_path = game_config.GetString("window", "font");
	window_settings.is_window_resizable = game_config.Get<bool>("window", "resizable");

	window.CreateWindow(window_settings);

	Actions::LoadKeybinds(window.GetInput(), "keybinds.txt");
}

void Game::Run()
{
	game_running = true;

	Surface surface(0, 0, window.GetTerminalWidth(), window.GetTerminalHeight());
	SetBorder(surface, BorderStyle::Double, Colors::White);

	UI ui;

	Label label(Point(1, 1), "Label");
	ui.Add(std::make_unique<Label>(label));

	Glyph g;
	g.character = 'A';
	g.color = Colors::Red;
	g.bg_color = BackgroundColors::DarkGrey;
	surface.Set(5, 5, g);

	surface.Print(1, 10, "Hello, highlighted text", Colors::Black, BackgroundColors::White);

	surface.PrintAligned(NULL, 20, "Hello", {AlignCenter});
	surface.PrintAligned(NULL, 20, "Left", { AlignLeft, 2 });
	surface.PrintAligned(NULL, 20, "Right", {AlignRight, 2});

	Button button1({ NULL, 25 }, "NEW WORLD", { AlignLeft, 10 });
	Button button2({ NULL, 26 }, "LOAD GAME", { AlignLeft, 10 });
	Button button3({ NULL, 27 }, "SETTINGS", { AlignLeft, 10 });
	Button button4({ NULL, 28 }, "QUIT", { AlignLeft, 10 });
	Menu menu({ button1, button2, button3, button4 }, MenuType::Horizontal);

	ui.Add(std::make_unique<Menu>(menu));

	// ~1300 fps 

	auto start = std::chrono::high_resolution_clock::now();
	uint64_t frames = 0;

	while (game_running && window.IsOpen())
	{
		window.Clear();
		window.HandleInput();

		ui.Update(window.GetInput());
		ui.Draw(surface);

		window.DrawSurface(surface);

		window.DisplayTerminal();

		/*
		frames++;

		if (frames % 1000 == 0)
		{
			auto now = std::chrono::high_resolution_clock::now();
			auto time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
			start = now;

			std::cout << "FPS: " << (1000.0 / (time_diff / 1000.0)) << " (" << time_diff << " ms)\n";
		}
		*/
	}
}
