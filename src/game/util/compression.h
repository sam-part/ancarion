#pragma once

#include <string>
#include <zlib.h>

namespace Gzip
{
	std::string Compress(const std::string& input, int level = Z_DEFAULT_COMPRESSION);
	void WriteToFile(const std::string& path, const std::string& input, int level = Z_DEFAULT_COMPRESSION);

	std::string Decompress(const std::string& input);
	std::string ReadFile(const std::string& path);
};