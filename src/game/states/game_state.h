#pragma once

#include "../../engine/sdl/window.h"
#include "../../engine/sdl/input.h"

class Game;

class GameState
{
public:
	virtual ~GameState() = default;

	virtual void Update(Game& game, Input& input) = 0;
	virtual void Draw(Window& window) = 0;
};