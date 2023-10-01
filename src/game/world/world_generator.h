#pragma once

#include "world.h"
#include "../util/random.h"

class WorldGenerator
{
private:
	World world;

	Random::FastRandom seed_rng;

public:
	void Generate();

	World GetWorld();
};