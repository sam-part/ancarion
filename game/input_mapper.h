#pragma once

#include <SDL2/SDL_keycode.h>
#include <unordered_map>
#include "../engine/sdl/window.h"

enum class InputState
{
	Pressed,
	Released
};

struct ActionState
{
	SDL_Keycode key;
	InputState state;
};

typedef uint16_t ActionID;

class InputMapper
{
private:
	std::unordered_map<ActionID, ActionState> actions;
	
public:
	void MapAction(ActionID action_id, ActionState action_state);

	bool IsTriggered(Window* window, ActionID action_id);
};