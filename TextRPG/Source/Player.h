//class representing the player

#pragma once

//variable size array
#include <vector>

#include "Items/Item.h"

class Player
{
	//old code that should be removed, oh well... don't feel like recompiling binaries
	friend class Game;
public:
	Player();
	~Player();

	//reset player stats
	void Reset();

	//called every loop in the OnUpdate loop in the Game class
	void OnUpdate();

	//setters and getters for m_Name, it's good practice to encapsulate member variables if you don't
	//want them to be accessed and modified directly
	const char* GetName() const { return m_Name; }
	void SetName(const char* name) { m_Name = name; }

	//add an item to the inventory
	void AddItem(Item* item);

	//remove an item from the inventory
	void PopItem(Item* item);
	void PopItem(const char* name);

	//returns if the player has an item in the inventory
	bool HasItem(Item* item) const;

	//use an item
	void UseItem(Item* item);
	void UseItem(const char* name);

	//equip an item
	void Equip(WeaponItem* item);
	void Equip(ArmorItem* item);

	//returns if armor or weapon is equipped
	bool IsWeaponEquipped() const;
	bool IsArmorEquipped() const;

	//handle a status effect
	void HandleStatusEffect(const StatusEffect& effect);

	//get the inventory
	const std::vector<Item*>& GetInventory() const { return m_Inventory; }

	//get various stats
	int GetHealth() const { return m_Health; }
	int GetMoney() const { return m_Money; }
	int GetDefense() const;
	int GetDamage() const;

	//returns if the player is alive
	bool IsAlive() const { return m_bAlive; }

private:
	//variable length array, it stores a list of Item*
	std::vector<Item*> m_Inventory;

	//set to a special value called nullptr, which means it's not pointing to anything
	WeaponItem* m_Weapon = nullptr;
	ArmorItem* m_Armor = nullptr;

	const char* m_Name = nullptr;

	//self explanatory
	bool m_bAlive = true;

	//various stats
	int m_Health = 20;
	int m_Defense = 10;
	int m_Strength = 15;
	int m_Money = 30;
};