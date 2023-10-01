#include "world_generator.h"

#include "../util/FastNoiseLite.h"
#include <chrono>
#include <iostream>
#include <algorithm>
#include <execution>

#include <FastNoise/FastNoise.h>
#include <unordered_map>

using namespace std::chrono;

void WorldGenerator::Generate()
{
	float elevation_scale = 0.05f;

	struct ElevationNoiseLayer
	{
		int num_octaves;
		float frequency;
		float weight;
	};

	std::vector<ElevationNoiseLayer> noise_layers = {
		{2, 1.0f, 1.0f},
		{4, 2.0f, 0.5f},
		{8, 4.0f, 0.125f}
	};

	Random::FastRandom offset_rng(seed_rng.GetNumber());
	const int max_offset = 16384;

	size_t sample_n = 100;
	uint64_t total_t = 0;

	for (int i = 0; i < sample_n; i++)
	{
		auto start = high_resolution_clock::now();

		world.seed = seed_rng.GetNumber();
		world.size = { 2048, 2048 };
		world.chunks.clear();
		world.chunks.resize(world.size.width * world.size.height);

		int num_layers = noise_layers.size();

		auto simplex_noise = FastNoise::New<FastNoise::OpenSimplex2>();
		auto elevation_noise = FastNoise::New<FastNoise::FractalFBm>();

		elevation_noise->SetSource(simplex_noise);

		std::vector<float> elevation_data(world.size.width * world.size.height);

		float min_value = FLT_MAX, max_value = FLT_MIN;

		for (int layer_idx = 0; layer_idx < num_layers; layer_idx++)
		{
			ElevationNoiseLayer noise_layer = noise_layers[layer_idx];

			int offset_x = offset_rng.GetNumber(-max_offset, max_offset);
			int offset_y = offset_rng.GetNumber(-max_offset, max_offset);

			elevation_noise->SetOctaveCount(noise_layer.num_octaves);
			elevation_noise->GenUniformGrid2D(elevation_data.data(), offset_x, offset_y, world.size.width, world.size.height, elevation_scale * noise_layer.frequency, world.seed);


			int index = 0;
			for (int y = 0; y < world.size.height; y++)
			{
				for (int x = 0; x < world.size.width; x++)
				{
					float& chunk_elevation = world.chunks[index].elevation;

					float layer_elevation = elevation_data[index] * noise_layer.weight;
					chunk_elevation += layer_elevation;

					if (layer_idx == num_layers - 1)
					{
						min_value = std::min(min_value, chunk_elevation);
						max_value = std::max(max_value, chunk_elevation);
					}

					index++;
				}
			}
		}

		int center_x = world.size.width / 2;
		int center_y = world.size.height / 2;
		int edge_cutoff = world.size.height / 10;

		float max_center_distance = std::sqrt((center_x * center_x) + (center_y * center_y));

		int index = 0;
		for (int y = 0; y < world.size.height; y++)
		{
			for (int x = 0; x < world.size.width; x++)
			{
				float& elevation = world.chunks[index++].elevation;

				// Normalize (0-1)
				elevation = (elevation - min_value) / (max_value - min_value);

				// Apply radial mask
				int center_distance_x = (center_x - x);
				int center_distance_y = (center_y - y);
				float distance = std::sqrt((center_distance_x * center_distance_x) + (center_distance_y * center_distance_y)); // can remove sqrt calculation
				elevation *= (1.0f - (distance / max_center_distance));

				// Get x and y distance from edge
				int edge_distance_x = std::min(x, world.size.width - x - 1);
				int edge_distance_y = std::min(y, world.size.height - y - 1);
				int edge_distance = std::min(edge_distance_x, edge_distance_y);

				// Apply edge falloff
				if (edge_distance <= edge_cutoff)
					elevation *= std::sqrt(static_cast<float>(edge_distance) / static_cast<float>(edge_cutoff));
			}
		}

		auto end = high_resolution_clock::now();
		total_t += duration_cast<microseconds>(end - start).count();
	}

	double avg = (total_t / sample_n) / 1000.0;
	std::cout << "Average for " << sample_n << " iterations: " << avg << "ms\n";
}

World WorldGenerator::GetWorld()
{
    return world;
}