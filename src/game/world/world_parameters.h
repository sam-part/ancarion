#pragma once

#include <cstdint>
#include <vector>
#include <string>

struct NoiseLayer
{
	int num_octaves;
	float frequency;
	float weight;
};

// Temporary
struct WorldParameters
{
	bool random_seed = false;
	uint64_t seed = 0;

	int width = 60;
	int height = 48;
	
	// Elevation generation
	float elevation_scale = 0.05f;
	std::vector<NoiseLayer> elevation_layers = {
		{2, 1.0f, 1.0f},
		{4, 2.0f, 0.5f},
		{8, 4.0f, 0.125f}
	};
	int max_elevation_offset = 16384;

	// Temperature generation
	float temperature_scale = 0.04f;
	int temperatue_octaves = 4;

	// Precipitation generation
	float precipitation_scale = 0.04f;
	int precipitation_octaves = 4;

	// Mountain generation
	float mountain_scale = 0.06f;
	int mountain_octaves = 8;
	float mountain_min_elevation = 0.4f;
	float mountain_threshold = 0.5f;
};