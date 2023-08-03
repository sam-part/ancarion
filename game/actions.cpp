#include "actions.h"

#include <SDL2/SDL_keyboard.h>
#include <iostream>
#include <string>
#include <vector>

struct KeybindInfo
{
	std::string name;
	uint16_t action_id;
	InputState press_type = InputState::Pressed;
};

struct SectionInfo
{
	std::string name;
	std::vector<KeybindInfo> keybinds;
};

std::vector<SectionInfo> keybinds_file_info = {
	{"general", {
		{"menu_up", Actions::General_MenuUp},
		{"menu_down", Actions::General_MenuDown},
		{"menu_left", Actions::General_MenuLeft},
		{"menu_right", Actions::General_MenuRight},
		{"enter", Actions::General_Enter},
		{"back", Actions::General_Back}
	}},
	{"worldgen", {
		{"view_up", Actions::Worldgen_ViewUp},
		{"view_down", Actions::Worldgen_ViewDown},
		{"view_left", Actions::Worldgen_ViewLeft},
		{"view_right", Actions::Worldgen_ViewRight},
	}}
};

void LoadKeybinds(InputMapper& input, const std::string& file_path)
{
	Config config(file_path);

	if (config.HasErrors())
	{
		std::cout << "Error: Could not load game keybinds\n";
		return;
	}

	auto MapAction = [&config, &input](std::string section, const KeybindInfo& keybind_info)
	{
		std::string key_name = config.GetString(section, keybind_info.name);

		SDL_Keycode key_code = SDL_GetKeyFromName(key_name.c_str());

		if (key_code == SDLK_UNKNOWN)
		{
			std::cout << "Unknown key " << key_name << " for action [" << section << "] " << keybind_info.name << "\n";
			return;
		}

		input.MapAction(keybind_info.action_id, {key_code, keybind_info.press_type});
	};

	for (SectionInfo& section : keybinds_file_info)
	{
		for (KeybindInfo& keybind : section.keybinds)
		{
			MapAction(section.name, keybind);
		}
	}
}
