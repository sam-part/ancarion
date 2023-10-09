#pragma once

#include <SDL2/SDL.h>
#include <cstdint>
#include <unordered_map>
#include <string>

#include "../types/point.h"

enum class InputState
{
	Pressed,
	Released
};

enum class MouseButton
{
	Left,
	Right,
	Middle
};

using ActionID = uint16_t;

class Input
{
private:
	std::unordered_map<ActionID, SDL_Keycode> actions{};

	// SDL will only poll one single key event per frame, overriding any previously held keys
	SDL_Keycode key_down = SDLK_UNKNOWN; 
	SDL_Keycode key_up = SDLK_UNKNOWN;

	SDL_Keymod keymods = KMOD_NONE;

	bool window_closed = false;
	bool window_resized = false;
	Point mouse_pos;

	const SDL_Keycode backspace_key = SDLK_BACKSPACE;
	std::string text_input = "";

public:
	void Update();

	void MapAction(ActionID id, SDL_Keycode);

	bool WindowShouldExit() const;
	bool WindowResized() const;
	bool ActionTriggered(ActionID id) const;

	// Returns the raw mouse position relative to the window
	Point GetMousePosition() const;

	void StartTextInput();
	void EndTextInput();
	std::string GetTextInput();
};