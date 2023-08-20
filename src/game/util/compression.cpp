#include "compression.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>

namespace Gzip
{
    constexpr int chunk_size = 16384;
    constexpr int window_bits = 15 | 16;

    std::string Compress(const std::string& input, int level)
    {
        const char* input_data = input.data();

        z_stream stream;
        stream.zalloc = Z_NULL;
        stream.zfree = Z_NULL;
        stream.opaque = Z_NULL;
        stream.avail_in = (uInt)(input.length() + 1);
        stream.next_in = (Bytef*)input_data;

        deflateInit2(&stream, level, Z_DEFLATED, window_bits, 8, Z_DEFAULT_STRATEGY);

        std::string output {};
        char* output_buffer = new char[chunk_size];

        do {
            stream.avail_out = (uInt)chunk_size;
            stream.next_out = (Bytef*)output_buffer;

            deflate(&stream, Z_FINISH);

            int output_size = chunk_size - stream.avail_out;
            output.append(output_buffer, output_size);
        } while (stream.avail_out == 0);

        deflateEnd(&stream);

        delete[] output_buffer;

        return output;
    }

    void WriteToFile(const std::string& path, const std::string& input, int level)
    {
        std::string compressed_data = Compress(input, level);

        std::ofstream output_file;
        output_file.open(path, std::ios::binary | std::ios::trunc);
        output_file.write(compressed_data.c_str(), compressed_data.size());
        output_file.close();
    }

    std::string Decompress(const std::string& input)
    {
        const char* input_data = input.data();

        z_stream stream;
        stream.zalloc = Z_NULL;
        stream.zfree = Z_NULL;
        stream.opaque = Z_NULL;
        stream.avail_in = (uInt)(input.length() + 1);
        stream.next_in = (Bytef*)input_data;

        inflateInit2(&stream, window_bits);

        std::string output {};
        char* output_buffer = new char[chunk_size];

        do {
            stream.avail_out = (uInt)chunk_size;
            stream.next_out = (Bytef*)output_buffer;

            int ret = inflate(&stream, Z_NO_FLUSH);
            if (ret != Z_OK && ret != Z_STREAM_END)
            {
                std::cout << "Error: Could not decompress gzip (" << ret << ")\n";
                break;
            }

            int output_size = chunk_size - stream.avail_out;
            output.append(output_buffer, output_size);
        } while (stream.avail_out == 0);

        inflateEnd(&stream);

        delete[] output_buffer;

        return output;
    }

    std::string ReadFile(const std::string& path)
    {
        std::ifstream input_file;
        input_file.open(path, std::ios::binary);

        if (!input_file.is_open())
        {
            std::cout << "Error: Could not open file " << path << " for decompression\n";
            return {};
        }

        std::stringstream input_stream;
        input_stream << input_file.rdbuf();

        return Decompress(input_stream.str());
    }
}

