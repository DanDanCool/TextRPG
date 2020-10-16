#include "Enemy.h"

#include "Util.h"
#include "Random.h"

Enemy CreateNormalEnemy(int step)
{
	Enemy enemy;
	enemy.Name = Util::GetRandomName(5, false);
	enemy.Health = (float)step * (Random::Float() + 0.2f) + 5;
	enemy.Strength = Util::Clamp(1, step / 5) + Random::UInt32(0, 5);
	enemy.Money = step + Random::UInt32(0, 50);

	return enemy;
}

Enemy CreateShinyEnemy(int step)
{
	Enemy enemy;
	enemy.Name = Util::GetRandomName(7, true);
	enemy.Health = (float)step * (Random::Float() + 0.8f);
	enemy.Strength = Util::Clamp(5, step / 3) + Random::UInt32(0, 20);
	enemy.Money = step * 2 + Random::UInt32(0, 100);

	return enemy;
}

void DestroyEnemy(Enemy& enemy)
{
	delete[] enemy.Name;
}