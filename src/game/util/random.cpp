#include "random.h"

namespace Random
{
	static inline uint64_t rotl(const uint64_t input, int n)
	{
		return (input << n) | (input >> (64 - n));
	}

	FastRandom::FastRandom()
	{
		state[0] = std::random_device{}();
		state[1] = std::random_device{}();
	}

	FastRandom::FastRandom(uint64_t seed)
	{
		Splitmix64 rng(seed);

		state[0] = rng.GetNumber();
		state[1] = rng.GetNumber();
	}

	uint64_t FastRandom::GetNumber()
	{
		uint64_t s0 = state[0];
		uint64_t s1 = state[1];

		uint64_t result = s0 + s1;
		s1 ^= s0;

		state[0] = rotl(s0, 55) ^ s1 ^ (s1 << 14);
		state[1] = rotl(s1, 36);

		return result;
	}

	// Implemented using Lemire's method, modified by M.E. O'Neill
	uint32_t FastRandom::GetNumber(uint32_t min, uint32_t max)
	{
		uint32_t range = max - min + 1;

		uint32_t n = static_cast<uint32_t>(GetNumber());
		uint64_t m = static_cast<uint64_t>(n) * static_cast<uint64_t>(range);
		uint32_t l = static_cast<uint32_t>(m);

		if (l < range)
		{
			#pragma warning(suppress:4146)
			uint32_t t = -range;

			if (t >= range)
			{
				t -= range;
				if (t >= range)
					t %= range;
			}

			while (l < t)
			{
				n = static_cast<uint32_t>(GetNumber());
				m = static_cast<uint64_t>(n) * static_cast<uint64_t>(range);
				l = static_cast<uint32_t>(m);
			}
		}

		return m >> 32;
	}

	float FastRandom::GetFloat()
	{
		uint32_t number = GetNumber() >> 41 | 0x3f800000;
		return *reinterpret_cast<float*>(&number) - 1.0f;
	}

	float FastRandom::GetFloat(float min, float max)
	{
		float range = max - min;
		return GetFloat() * range + min;
	}

	double FastRandom::GetDouble()
	{
		uint64_t number = GetNumber() >> 12 | 0x3FF0000000000000;
		return *reinterpret_cast<double*>(&number) - 1.0;
	}

	double FastRandom::GetDouble(double min, double max)
	{
		double range = max - min;
		return GetDouble() * range + min;
	}

	Splitmix64::Splitmix64()
	{
		state = std::random_device{}();
	}

	Splitmix64::Splitmix64(uint64_t seed)
		: state(seed)
	{}

	uint64_t Splitmix64::GetNumber()
	{
		state += 0x9e3779b97f4a7c15;
		uint64_t z = state;
		z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
		z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
		return z ^ (z >> 31);
	}

}