#pragma once

#include <string>

struct Enemy
{
	const char* Name;
	int Health;
	int Strength;
	int Money;
};

Enemy CreateNormalEnemy(int step);
Enemy CreateShinyEnemy(int step);

void DestroyEnemy(Enemy& enemy);