#pragma once

#include <vector>
#include <string>
#include "../engine/sdl/input.h"
#include "config.h"

namespace Actions
{	enum Actions : ActionID
	{
		General_MenuUp,
		General_MenuDown,
		General_MenuLeft,
		General_MenuRight,
		General_Continue,
		General_Back,

		Worldgen_Regenerate,
		Worldgen_ViewUp,
		Worldgen_ViewDown,
		Worldgen_ViewLeft,
		Worldgen_ViewRight,
		Worldgen_ViewUpFast,
		Worldgen_ViewDownFast,
		Worldgen_ViewLeftFast,
		Worldgen_ViewRightFast,
	};

	void LoadKeybinds(Input& input, const std::string& path);
}