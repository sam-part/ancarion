#include "actions.h"

#include <iostream>

namespace Actions
{
	struct ActionInfo
	{
		ActionID id;
		std::string name;
	};

	struct SectionInfo
	{
		std::string name;
		std::vector<ActionInfo> actions;
	};

	std::vector<SectionInfo> actions = {
		{"general", {
			{General_MenuUp, "menu_up"},
			{General_MenuDown, "menu_down"},
			{General_MenuLeft, "menu_left"},
			{General_MenuRight, "menu_right"},
			{General_Continue, "continue"},
			{General_Back, "back"}
		}},

		{"worldgen", {
			{Worldgen_Regenerate, "new_world"},
			{Worldgen_ViewUp, "view_up"},
			{Worldgen_ViewDown, "view_down"},
			{Worldgen_ViewLeft, "view_left"},
			{Worldgen_ViewRight, "view_right"},
		}}
	};

	void LoadKeybinds(Input& input, const std::string& path)
	{
		Config config(path);

		if (config.HasErrors())
		{
			std::cout << "Could not load keybinds (" << path << ")\n";
			return;
		}

		for (SectionInfo& section : actions)
		{
			for (ActionInfo& action_info : section.actions)
			{
				std::string key_name = config.GetString(section.name, action_info.name);
				SDL_Keycode key = SDL_GetKeyFromName(key_name.c_str());

				if (key == SDLK_UNKNOWN)
				{
					std::cout << "Action [" << section.name << "] " << action_info.name << ": could not find key '" << key_name << "'\n";
					continue;
				}

				input.MapAction(action_info.id, key);
			}
		}
	}
}