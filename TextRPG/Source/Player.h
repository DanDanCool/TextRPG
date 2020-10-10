#pragma once

#include <vector>

#include "Items/Item.h"

class Player
{
public:
	Player();
	~Player();

	void AddItem(Item* item);
	void PopItem(Item* item);

	void UseItem(Item* item);

	void Equip(WeaponItem* item);
	void Equip(ArmorItem* item);

private:
	std::vector<Item*> m_Inventory;

	WeaponItem* m_Weapon = nullptr;
	ArmorItem* m_Armor = nullptr;

	int m_Health = 3;
	int m_Defense = 0;
	int m_Strength = 2;
	int m_Money = 30;
};