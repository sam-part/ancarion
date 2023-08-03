#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <unordered_set>
#include "surface.h"

struct WindowSettings
{
	const char* window_name;

	unsigned int terminal_width;
	unsigned int terminal_height;

	std::string font_path;
	std::string icon_path;

	bool is_window_resizable;
};

class Window
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	unsigned int window_width, window_height;
	const char* window_name;

	SDL_Texture* font_texture;
	unsigned int font_width, font_height;

	std::vector<SDL_Texture*> background_color_textures;

	unsigned int terminal_width, terminal_height;
	std::vector<Glyph> terminal;

	std::unordered_set<SDL_Keycode> key_presses;
	std::unordered_set<SDL_Keycode> key_releases;

	bool window_open = false;
	bool initialized = false;

public:
	void CreateWindow(const WindowSettings& window_settings);
	~Window();

	void ResizeTerminal(int new_terminal_width, int new_terminal_height);
	int GetTerminalWidth();
	int GetTerminalHeight();

	void PollEvents();
	void Clear();
	void DrawSurface(const Surface& surface);
	void DisplayTerminal();

	bool IsKeyDown(SDL_Keycode key);
	bool WasKeyReleased(SDL_Keycode key);

	bool IsOpen();
	void Close();
};