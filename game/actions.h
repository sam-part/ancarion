#pragma once

#include "config.h"
#include "input_mapper.h"

namespace Actions
{
	enum : uint16_t
	{
		General_MenuUp,
		General_MenuDown,
		General_MenuLeft,
		General_MenuRight,
		General_Enter,
		General_Back,

		Worldgen_ViewUp,
		Worldgen_ViewDown,
		Worldgen_ViewLeft,
		Worldgen_ViewRight
	};
}

void LoadKeybinds(InputMapper& input, const std::string& file_path);