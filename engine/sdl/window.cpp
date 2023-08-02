#include "window.h"

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

	// Initialize background colors (these are limited to 16 base colors to avoid recreating them multiple times every frame)
	SDL_Surface* bg_color_surface = SDL_CreateRGBSurface(NULL, font_width, font_height, 32, 0, 0, 0, 0);
	for (int i = 0; i < BackgroundColors::NUM_BACKGROUND_COLORS; i++)
	{
		Color bg_color = BackgroundColors::colors[i];

		SDL_FillRect(bg_color_surface, NULL, SDL_MapRGB(bg_color_surface->format, bg_color.r, bg_color.g, bg_color.b));
		background_color_textures.push_back(SDL_CreateTextureFromSurface(renderer, bg_color_surface));
	}

	terminal.resize(terminal_width * terminal_height);

	window_open = true;
}

void Window::ResizeTerminal(int new_terminal_width, int new_terminal_height)
{
	terminal_width = new_terminal_width;
	terminal_height = new_terminal_height;

	window_width = terminal_width * font_width;
	window_height = terminal_height * font_height;

	SDL_SetWindowSize(window, window_width, window_height);

	terminal.clear();
	terminal.resize(terminal_width * terminal_height);
}

int Window::GetTerminalWidth()
{
	return terminal_width;
}

int Window::GetTerminalHeight()
{
	return terminal_height;
}

void Window::PollEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			Close();
			break;
		case SDL_KEYDOWN:
			break;
		case SDL_KEYUP:
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				window_width = event.window.data1;
				window_height = event.window.data2;

				//ResizeTerminal(new_terminal_width, new_terminal_height);
			}

			break;
		default:
			break;
		}
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
			Glyph glyph = terminal[index];

			SDL_Rect src = { (glyph.character % 16) * font_width, (glyph.character / 16) * font_height, font_width, font_height };
			SDL_Rect dest = { x * font_width, y * font_height, font_width, font_height };


			if (glyph.bg_color != BackgroundColors::None && glyph.bg_color < BackgroundColors::NUM_BACKGROUND_COLORS)
				SDL_RenderCopy(renderer, background_color_textures[glyph.bg_color], NULL, &dest);

			SDL_SetTextureColorMod(font_texture, glyph.color.r, glyph.color.g, glyph.color.b);
			SDL_RenderCopy(renderer, font_texture, &src, &dest);

			index++;
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
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	window = nullptr;
	renderer = nullptr;
}
