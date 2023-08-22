#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include "../../engine/types/rect.h"

struct ChunkInfo
{
	float elevation = 0.0f;
	float precipitation = 0.0f;
	float temperature = 0.0f;
};

class WorldGenerator;

class World
{
	friend class WorldGenerator;

private:
	std::string name;
	uint32_t seed;

	Size size;

	std::vector<ChunkInfo> chunks;

	ChunkInfo& chunk(int x, int y);

public:
	const ChunkInfo& GetChunk(int x, int y);
	const ChunkInfo& GetChunk(int index);
};