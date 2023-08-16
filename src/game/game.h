#pragma once

#include "../engine/ascii_engine.h"
#include "ui/ui.h"
#include "config.h"
#include "actions.h"

class Game
{
private:
	const std::string config_path = "settings.txt";
	Config game_config;

	Window window;
	// StateManager state_manager;

	bool game_running = false;

public:
	Game();

	void Run();
};