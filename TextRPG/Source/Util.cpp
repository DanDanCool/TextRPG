#include "Util.h"

#include "Random.h"

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
		if (addApostrophe)
			length++;

		char* str = new char[length + 1];
		str[0] = UPPER_ALPHABET[Random::UInt32(0, 25)];

		for (uint32_t i = 1; i < length; i++)
		{
			str[i] = LOWER_ALPHABET[Random::UInt32(0, 25)];

			if (addApostrophe && i == length / 2)
				str[++i] = '\'';
		}

		str[length] = '\0';

		return str;
	}

	const char* GetRandomName(uint32_t length, bool addApostrophe, const char* name)
	{
		std::string str;
		str += GetRandomName(length, addApostrophe);
		str += name;

		return str.c_str();
	}
}