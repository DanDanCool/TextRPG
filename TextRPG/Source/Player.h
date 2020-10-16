#pragma once

#include <vector>

#include "Items/Item.h"

class Player
{
	friend class Game;
public:
	Player();
	~Player();

	void Reset();

	void OnUpdate();

	const char* GetName() const { return m_Name; }
	void SetName(const char* name) { m_Name = name; }

	void AddItem(Item* item);
	void PopItem(Item* item);
	void PopItem(const char* name);

	bool HasItem(Item* item) const;

	void UseItem(Item* item);
	void UseItem(const char* name);

	void Equip(WeaponItem* item);
	void Equip(ArmorItem* item);

	bool IsWeaponEquipped() const;
	bool IsArmorEquipped() const;

	void HandleStatusEffect(const StatusEffect& effect);

	const std::vector<Item*>& GetInventory() const { return m_Inventory; }

	int GetHealth() const { return m_Health; }
	int GetMoney() const { return m_Money; }
	int GetDefense() const;
	int GetDamage() const;

	bool IsAlive() const { return m_bAlive; }

private:
	std::vector<Item*> m_Inventory;

	WeaponItem* m_Weapon = nullptr;
	ArmorItem* m_Armor = nullptr;

	const char* m_Name = nullptr;

	bool m_bAlive = true;

	int m_Health = 20;
	int m_Defense = 10;
	int m_Strength = 15;
	int m_Money = 30;
};