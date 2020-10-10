#pragma once

#include <string>

struct Enemy
{
	std::string Name;
	int Health;
	int Strength;
	int Money;
};

Enemy CreateNormalEnemy();
Enemy CreateShinyEnemy();