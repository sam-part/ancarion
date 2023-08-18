#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <unordered_set>
#include "surface.h"
#include "input.h"
#include "../types/size.h"

struct WindowSettings
{
	const char* window_name;

	int terminal_width;
	int terminal_height;

	std::string font_path;
	std::string icon_path;

	bool is_window_resizable;
	int min_terminal_width;
	int min_terminal_height;
};

class Window
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	int window_width, window_height;
	const char* window_name;

	SDL_Texture* font_texture;
	int font_width, font_height;

	SDL_Texture* background_tile_texture;

	int terminal_width, terminal_height;
	std::vector<Glyph> terminal;

	Input input;

	bool window_open = false;
	bool initialized = false;

public:
	void CreateWindow(const WindowSettings& window_settings);
	~Window();

	void ResizeTerminal(int new_terminal_width, int new_terminal_height);
	int GetTerminalWidth();
	int GetTerminalHeight();
	Size GetWindowSize();

	Input& GetInput();

	void HandleInput();
	void Clear();
	void DrawSurface(const Surface& surface);
	void DisplayTerminal();

	bool IsOpen();
	void Close();
};