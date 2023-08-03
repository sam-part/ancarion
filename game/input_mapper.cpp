#include "input_mapper.h"

void InputMapper::MapAction(ActionID action_id, ActionState action_state)
{
	actions[action_id] = action_state;
}

bool InputMapper::IsTriggered(Window* window, ActionID action_id)
{
	auto it = actions.find(action_id);
	if (it == actions.end())
		return false;

	switch (it->second.state)
	{
	case InputState::Pressed:
		return window->IsKeyDown(it->second.key);
		break;
	case InputState::Released:
		return window->WasKeyReleased(it->second.key);
		break;
	default:
		return false;
	}
}
