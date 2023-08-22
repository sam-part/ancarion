#pragma once

#include "world.h"
#include <mutex>

struct WorldGenerationStage
{
	std::string message {};
	int percent_finished = 0;
};

class WorldGenerator
{
private:
	WorldGenerationStage current_stage;
	bool stage_changed = false;
	std::mutex stage_mutex;

	void ChangeStage(std::string message, int percent_finished);

public:
	World Generate();

	bool StageChanged();
	WorldGenerationStage GetCurrentStage();
};