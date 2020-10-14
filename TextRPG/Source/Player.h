#pragma once

#include <vector>

#include "Items/Item.h"

class Player
{
	friend class Game;
public:
	Player();
	~Player();

	const char* GetName() const { return m_Name; }
	void SetName(const char* name) { m_Name = name; }

	void AddItem(Item* item);
	void PopItem(Item* item);

	bool HasItem(Item* item) const;

	void UseItem(Item* item);

	void Equip(WeaponItem* item);
	void Equip(ArmorItem* item);

	bool IsWeaponEquipped() const;
	bool IsArmorEquipped() const;

	void HandleStatusEffect(const StatusEffect& effect);

	int GetHealth() const { return m_Health; }
	int GetDefense() const { return m_Defense; }
	int GetStrength() const { return m_Strength; }
	int GetMoney() const { return m_Money; }

	bool IsAlive() const { return m_bAlive; }

private:
	std::vector<Item*> m_Inventory;

	WeaponItem* m_Weapon = nullptr;
	ArmorItem* m_Armor = nullptr;

	const char* m_Name = nullptr;

	bool m_bAlive = true;

	int m_Health = 3;
	int m_Defense = 0;
	int m_Strength = 2;
	int m_Money = 30;
};