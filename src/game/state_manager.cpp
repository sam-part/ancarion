#include "state_manager.h"

void StateManager::PushState(std::shared_ptr<GameState> state)
{
	state->Initialize();
	states.push_back(std::move(state));
}

void StateManager::PopState()
{
	if(!states.empty())
		states.pop_back();
}

void StateManager::Clear()
{
	states.clear();
}

void StateManager::UpdateStates(Game& game, Input& input)
{
	for (auto& state : states)
		state->Update(game, input);
}

void StateManager::DrawStates(Window& window)
{
	for (auto& state : states)
		state->Draw(window);
}