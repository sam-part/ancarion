#pragma once

#include "states/game_state.h"
#include <memory>
#include <vector>

class StateManager
{
private:
	std::vector<std::shared_ptr<GameState>> states{};

public:
	void PushState(std::shared_ptr<GameState> state);
	void PopState();
	void Clear();

	void UpdateStates(Game& game, Input& input);
	void DrawStates(Window& window);
};