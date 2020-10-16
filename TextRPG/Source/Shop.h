#pragma once

class Item;

struct Shop
{
	int Costs[4];

	Item* HealthItem;
	Item* WeaponItem;
	Item* ArmorItem;
	
	const char* ScoreItemName;
};

Shop CreateShop(int step);
inline Shop CreateShop1();
inline Shop CreateShop2();
inline Shop CreateShop3();
inline Shop CreateShop4();