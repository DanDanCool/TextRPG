#pragma once

#include <stdint.h>

namespace Util
{
	int Clamp(int min, int max, int value);
	int Clamp(int min, int value);

	const char* GetRandomName(uint32_t length, bool addApostrophe);
	const char* GetRandomName(uint32_t length, bool addApostrophe, const char* name);
}