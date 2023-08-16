#include "input.h"

#include <iostream>

void Input::Update()
{
	key_down = SDLK_UNKNOWN;
	key_up = SDLK_UNKNOWN;

	window_resized = false;

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			window_closed = true;
			break;
		case SDL_KEYDOWN:
			key_down = event.key.keysym.sym;

			if (SDL_IsTextInputActive() && (key_down == backspace_key) && !text_input.empty())
				text_input.pop_back();

			break;
		case SDL_KEYUP:
			key_up = event.key.keysym.sym;
			break;
		case SDL_TEXTINPUT:
			text_input += event.text.text;
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				window_resized = true;
			break;
		default:
			break;
		}
	}

	keymods = SDL_GetModState();

	SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
}

void Input::MapAction(ActionID id, SDL_Keycode key)
{
	actions[id] = key;
}

bool Input::WindowShouldExit() const
{
	return window_closed;
}

bool Input::WindowResized() const
{
	return window_resized;
}

bool Input::ActionTriggered(ActionID id) const
{
	auto it = actions.find(id);

	if (it == actions.end())
		return false;

	return (it->second == key_down);
}

Point Input::GetMousePosition() const
{
	return mouse_pos;
}

void Input::StartTextInput()
{
	text_input = "";
	SDL_StartTextInput();
}

void Input::EndTextInput()
{
	SDL_StopTextInput();
}

std::string Input::GetTextInput()
{
	return text_input;
}
