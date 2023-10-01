#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include "../../engine/types/rect.h"

enum class TerrainType
{
	None = 0,

	Ocean,
	Land,
	Mountain
};

struct ChunkInfo
{
	float elevation = 0.0f;
	float precipitation = 0.0f;
	float temperature = 0.0f;

	TerrainType terrain = TerrainType::None;
	//BiomeType biome;
};

class WorldGenerator;

class World
{
	friend class WorldGenerator;

private:
	std::string name;
	uint64_t seed = 0;

	Size size;

	std::vector<ChunkInfo> chunks;

	ChunkInfo& chunk(int x, int y);

public:
	const ChunkInfo& GetChunk(int x, int y);
	const ChunkInfo& GetChunk(int index);

	Size GetSize();
};