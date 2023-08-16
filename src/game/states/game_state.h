#pragma once

#include "../../engine/sdl/window.h"

class Game;

class GameState
{
public:
	virtual ~GameState() = 0;

	virtual void Initialize() = 0;
	virtual void Update(Game& game) = 0;
	virtual void Draw(Window& window) = 0;
};