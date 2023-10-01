#include "world_parameters.h"

#include "../config.h"

WorldParameters LoadWorldParameters(const std::string& file_path)
{
	WorldParameters parameters;

	Config config(file_path);

	return parameters;
}