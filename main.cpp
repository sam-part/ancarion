#include "engine/ascii_engine.h"

#include "game/util/random.h"
#include "game/game.h"

#include <chrono>
#include <unordered_map>
using namespace std::chrono;

int main(int argc, char* args[])
{
	Game game;
	game.Run();
	/*
	size_t num = 1000000000;

	Random::FastRandom fast_random(0);

	std::cout << "Random number tests:\n";

	auto start = high_resolution_clock::now();
	for (size_t i = 0; i < num; i++)
	{
		volatile uint64_t res = fast_random.GetNumber();
	}
	auto end = high_resolution_clock::now();
	auto diff = duration_cast<nanoseconds>(end - start).count();
	auto total = (diff / (1000 * 1000));

	std::cout << "FastRandom (Xorshiro128+): " << (total / 1000.0) << "s for " << num << " iterations (" << ((total / 1000.0 == 0) ? "undefined" : std::to_string((uint64_t)(num / (total / 1000.0)))) << "/s)\n";
 
	std::cout << "\n\nRange tests:\n";

	uint32_t min = 1;
	uint32_t max = 997;

	start = high_resolution_clock::now();
	for (size_t i = 0; i < num; i++)
	{
		volatile uint64_t res = fast_random.Range(min, max);
	}
	end = high_resolution_clock::now();
	diff = duration_cast<nanoseconds>(end - start).count();
	total = (diff / (1000 * 1000));

	std::cout << "FastRandom (Xorshiro128+) - Lemire's method: " << (total / 1000.0) << "s for " << num << " iterations (" << ((total / 1000.0 == 0) ? "undefined" : std::to_string((uint64_t)(num / (total / 1000.0)))) << "/s)\n";
	
	start = high_resolution_clock::now();
	for (size_t i = 0; i < num; i++)
	{
		volatile uint64_t res = (fast_random.GetNumber() % (max - min + 1)) + min;
	}
	end = high_resolution_clock::now();
	diff = duration_cast<nanoseconds>(end - start).count();
	total = (diff / (1000 * 1000));

	std::cout << "FastRandom (Xorshiro128+) - Modulo: " << (total / 1000.0) << "s for " << num << " iterations (" << ((total / 1000.0 == 0) ? "undefined" : std::to_string((uint64_t)(num / (total / 1000.0)))) << "/s)\n";
	*/

	//Random::FastRandom fast_random(0);

	/*
	std::unordered_map<uint32_t, size_t> count;
	size_t num = 100000000;

	uint32_t min = 1;
	uint32_t max = 7;

	for (size_t i = 0; i < num; i++)
	{
		uint32_t num = fast_random.Range(min, max);
		count[num]++;
	}

	for (auto& num : count)
	{
		std::cout << num.first << ": " << num.second << "\n";
	}
	*/

	/*
	size_t num = 1000000000;
	size_t out_range = 0;

	std::cout << "Random number tests:\n";

	auto start = high_resolution_clock::now();
	for (size_t i = 0; i < num; i++)
	{
		double res = fast_random.GetDouble(-1.05773, 4.5562);
		if (res < -1.05773 || res > 4.5562)
		{
			std::cout << res << "\n";
			out_range++;
		}
		//volatile float res = fast_random.GetFloat(4.7f, 9.5f);
		//std::cout << res << "\n";
	}
	auto end = high_resolution_clock::now();
	auto diff = duration_cast<nanoseconds>(end - start).count();
	auto total = (diff / (1000 * 1000));

	std::cout << "FastRandom (Xorshiro128+) reinterpret_cast floats: " << (total / 1000.0) << "s for " << num << " iterations (" << ((total / 1000.0 == 0) ? "undefined" : std::to_string((uint64_t)(num / (total / 1000.0)))) << "/s)\n";
	*/

	/*
	const int width = 100;
	const int height = 60;

	WindowSettings window_settings;
	window_settings.window_name = "Ancarion";
	window_settings.terminal_width = width;
	window_settings.terminal_height = height;
	window_settings.font_path = "assets/font.png";
	window_settings.is_window_resizable = true;

	Window window;
	window.CreateWindow(window_settings);

	Surface surface(0, 0, width, height);
	surface.Print(0, 0, "Hello!");

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			Glyph ch;
			ch.character = rand() % 255;
			ch.color = Color{ (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255) };
			ch.bg_color = Color{ (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255) };
			surface.Set(x, y, ch);
		}
	}

	Surface surface2(10, 10, 20, 10);
	surface2.Print(1, 1, "Hello! Border test");
	SetBorder(surface2, BorderStyle::Normal, Colors::White);

	Surface surface3(10, 30, 30, 8);
	surface3.Print(1, 1, "Hello! Double border test");
	SetBorder(surface3, BorderStyle::Double, Colors::DarkGrey);

	Rect rect(Point(1, 1), Size(4, 4));
	SetBorder(surface, rect, BorderStyle::Normal, Colors::DarkGreen);

	while (window.IsOpen())
	{
		//window.Clear();
		window.PollEvents();

		window.DrawSurface(surface);
		window.DrawSurface(surface2);
		window.DrawSurface(surface3);

		window.DisplayTerminal();
	}
	*/

	return 0;
}