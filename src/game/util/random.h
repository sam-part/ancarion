#pragma once

#include <random>

namespace Random
{
	// Fast pseudorandom number generation using xoroshiro128+
	// Generates numbers within range using Lemire's method, modified by M.E. O'Neill
	class FastRandom
	{
	private:
		uint64_t state[2];

	public:
		FastRandom();
		FastRandom(uint64_t seed);

		uint64_t GetNumber();
		uint32_t GetNumber(uint32_t min, uint32_t max);
		int32_t GetNumber(int32_t min, int32_t max);

		float GetFloat();
		float GetFloat(float min, float max);

		double GetDouble();
		double GetDouble(double min, double max);
	};

	// Splitmix64 pseudorandom number generator 
	// Used to seed the internal states of the FastRandom class 
	class Splitmix64
	{
	private:
		uint64_t state;

	public:
		Splitmix64();
		Splitmix64(uint64_t seed);

		uint64_t GetNumber();
	};
}

/*
class Random
{
private:
	std::mt19937 generator;

public:
	Random()
	{
		generator = std::mt19937(std::random_device{}());
	}

	Random(uint32_t seed)
	{
		generator = std::mt19937(seed);
	}

	void Seed(uint32_t seed)
	{
		generator.seed(seed);
	}

	template<typename T>
	T GetInt(T min, T max)
	{
		return std::uniform_int_distribution<T>(min, max)(generator);
	}

	template<typename T>
	T GetInt(const std::uniform_int_distribution<T>& distr)
	{
		return distr(generator);
	}

	template<typename T>
	T GetFloat(T min, T max)
	{
		return std::uniform_real_distribution<T>(min, max)(generator);
	}

	template<typename T>
	T GetFloat(const std::uniform_real_distribution<T>& distr)
	{
		return distr(generator);
	}

	template<typename T>
	std::uniform_int_distribution<T> GetIntDistribution(T min, T max)
	{
		return std::uniform_int_distribution<T>(min, max);
	}

	template<typename T>
	std::uniform_real_distribution<T> GetFloatDistribution(T min, T max)
	{
		return std::uniform_real_distribution<T>(min, max);
	}

	uint32_t GenerateSeed()
	{
		return GetInt<uint32_t>(0, std::numeric_limits<uint32_t>::max());
	}

	int GetWeightedIndex(const std::vector<float>& weights)
	{
		return std::discrete_distribution<int>(weights.begin(), weights.end())(generator);
	}
};
*/