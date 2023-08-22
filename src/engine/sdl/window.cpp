#include "window.h"
#include <iostream>

void Window::CreateWindow(const WindowSettings& window_settings)
{
	window_name = window_settings.window_name;

	terminal_width = window_settings.terminal_width;
	terminal_height = window_settings.terminal_height;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize, SDL_Error: " << SDL_GetError() << "\n";
		return;
	}

	// Load font surface
	SDL_Surface* terminal_font_surface = IMG_Load(window_settings.font_path.c_str());
	if (terminal_font_surface == NULL)
	{
		std::cout << "IMG_Error: " << IMG_GetError() << "\n";
		return;
	}

	font_width = terminal_font_surface->w / 16;
	font_height = terminal_font_surface->h / 16;

	window_width = terminal_width * font_width;
	window_height = terminal_height * font_height;

	// Create window 
	Uint32 window_flags = SDL_WINDOW_SHOWN;
	if (window_settings.is_window_resizable)
		window_flags |= SDL_WINDOW_RESIZABLE;

	window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, window_flags);
	if (window == NULL)
	{
		std::cout << "SDL could not create window, SDL_Error: " << SDL_GetError() << "\n";
		return;
	}

	if (window_settings.is_window_resizable)
		SDL_SetWindowMinimumSize(window, window_settings.min_terminal_width * font_width, window_settings.min_terminal_height * font_height);

	// Create renderer
	Uint32 renderer_flags = SDL_RENDERER_ACCELERATED;

	renderer = SDL_CreateRenderer(window, -1, renderer_flags);
	if (renderer == NULL)
	{
		std::cout << "SDL could not create renderer, SDL_Error: " << SDL_GetError() << "\n";
		return;
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Create font texture
	Uint32 color_key = SDL_MapRGB(terminal_font_surface->format, 255, 0, 255);
	SDL_SetColorKey(terminal_font_surface, SDL_TRUE, color_key);

	font_texture = SDL_CreateTextureFromSurface(renderer, terminal_font_surface);

	SDL_FreeSurface(terminal_font_surface);
	terminal_font_surface = nullptr;

	// Create background tile texture
	SDL_Surface* background_tile_surface = SDL_CreateRGBSurface(NULL, font_width, font_height, 32, 0, 0, 0, 0);
	SDL_FillRect(background_tile_surface, NULL, SDL_MapRGB(background_tile_surface->format, 255, 255, 255));

	background_tile_texture = SDL_CreateTextureFromSurface(renderer, background_tile_surface);

	SDL_FreeSurface(background_tile_surface);
	background_tile_surface = nullptr;

	terminal.resize(terminal_width * terminal_height);

	window_open = true;

	input.EndTextInput();
}

int Window::GetTerminalWidth() const
{
	return terminal_width;
}

int Window::GetTerminalHeight() const
{
	return terminal_height;
}

Size Window::GetWindowSize() const
{
	return Size(window_width, window_height);
}

Input& Window::GetInput()
{
	return input;
}

void Window::HandleInput()
{
	input.Update();
	window_open = !input.WindowShouldExit();

	int prev_window_width = window_width;
	int prev_window_height = window_height;

	SDL_GetWindowSize(window, &window_width, &window_height);

	if (input.WindowResized())
	{
		terminal_width = window_width / font_width;
		terminal_height = window_height / font_height;

		terminal.clear();
		terminal.resize(terminal_width * terminal_height);
	}
}

void Window::Clear()
{
	Glyph empty_glyph;
	std::fill(terminal.begin(), terminal.end(), empty_glyph);
}

void Window::DrawSurface(const Surface& surface)
{
	const SurfaceData& surface_data = surface.GetData();

	int index = 0;
	for (int y = surface_data.origin_y; y < surface_data.origin_y + surface_data.height; y++)
	{
		if (y < 0 || y >= terminal_height)
		{
			index += terminal_width;
			continue;
		}

		for (int x = surface_data.origin_x; x < surface_data.origin_x + surface_data.width; x++)
		{
			if (x < 0 || x >= terminal_width)
			{
				index++;
				continue;
			}

			terminal[y * terminal_width + x] = surface_data.data[index];
			index++;
		}
	}
}

void Window::DisplayTerminal()
{
	SDL_RenderClear(renderer);

	// Draw characters to window
	int index = 0;
	for (int y = 0; y < terminal_height; y++)
	{
		for (int x = 0; x < terminal_width; x++)
		{
			Glyph glyph = terminal[index++];

			if (glyph.character == Characters::Empty)
				continue;

			SDL_Rect src = { (glyph.character % 16) * font_width, (glyph.character / 16) * font_height, font_width, font_height };
			SDL_Rect dest = { x * font_width, y * font_height, font_width, font_height };

			// Render background color (if necessary)
			if (glyph.bg_color.r != 0 || glyph.bg_color.g != 0 || glyph.bg_color.b != 0)
			{
				SDL_SetTextureColorMod(background_tile_texture, glyph.bg_color.r, glyph.bg_color.g, glyph.bg_color.b);
				SDL_RenderCopy(renderer, background_tile_texture, NULL, &dest);
			}

			// Render tile to screen
			SDL_SetTextureColorMod(font_texture, glyph.color.r, glyph.color.g, glyph.color.b);
			SDL_RenderCopy(renderer, font_texture, &src, &dest);
		} 
	}

	SDL_RenderPresent(renderer);
}

bool Window::IsOpen()
{
	return window_open;
}

void Window::Close()
{
	window_open = false;
}

Window::~Window()
{
	SDL_DestroyTexture(font_texture);
	SDL_DestroyTexture(background_tile_texture);

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	window = nullptr;
	renderer = nullptr;
}