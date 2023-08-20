#include "game.h"
#include <chrono>
#include <iostream>

#include "states/main_menu.h"

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
	state_manager.PushState(std::make_shared<MainMenu>(*this, window));

	game_running = true;

	while (game_running && window.IsOpen())
	{
		window.Clear();
		window.HandleInput();

		state_manager.UpdateStates(*this, window.GetInput());
		state_manager.DrawStates(window);

		window.DisplayTerminal();
	}
}

void Game::Exit()
{
	game_running = false;
}
