#pragma once

class Item;

struct Shop
{
	int* Costs;
	Item** Items;
	const char* ScoreItemName;
};

Shop CreateShop(int step);
Shop CreateShop1();
Shop CreateShop2();
Shop CreateShop3();
Shop CreateShop4();