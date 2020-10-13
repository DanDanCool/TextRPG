#include "Util.h"

#include "Random.h"
#include <string>

const char UPPER_ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char LOWER_ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";

namespace Util
{
	int Clamp(int min, int max, int value)
	{
		return value > max ? max : Clamp(min, value);
	}

	int Clamp(int min, int value)
	{
		return value > min ? value : min;
	}

	const char* GetRandomName(uint32_t length, bool addApostrophe)
	{
		std::string str;
		str += UPPER_ALPHABET[Random::UInt32(0, 25)];

		for (uint32_t i = 0; i < length - 1; i++)
		{
			str += LOWER_ALPHABET[Random::UInt32(0, 25)];

			if (addApostrophe && i == length / 2)
				str += '\'';
		}

		return str.c_str();
	}

	const char* GetRandomName(uint32_t length, bool addApostrophe, const char* name)
	{
		std::string str;
		str += GetRandomName(length, addApostrophe);
		str += name;

		return str.c_str();
	}
}