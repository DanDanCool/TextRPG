#pragma once

#include "../StatusEffect.h"

class Player;

class Item
{
public:
	virtual ~Item() = default;

	virtual StatusEffect Use();
	virtual bool IsEquippable() { return false; }

	const char* GetName() const { return m_Name; }

protected:
	Item() = default;
	
	const char* m_Name;
};

class HealthItem : public Item
{
public:
	virtual StatusEffect Use() override;
	bool IsEquippable() final { return false; }

protected:
	int m_HealAmount = 0;
};

class EquippableItem : public Item
{
public:
	virtual StatusEffect OnEquip() { return Item::Use(); }
	virtual StatusEffect OnUnequip() { return Item::Use(); }

	virtual StatusEffect OnUpdate() { return Item::Use(); }

	bool IsEquippable() final { return true; }

	virtual bool IsWeapon() { return false; }
	virtual bool IsArmor() { return false; }

protected:
	EquippableItem() = default;
};

class WeaponItem : public EquippableItem
{
public:
	virtual StatusEffect Use() override;
	bool IsWeapon() final { return true; }
	int GetDamage() const { return m_Damage; }

protected:
	int m_Damage;
};

class ArmorItem : public EquippableItem
{
public:
	bool IsArmor() final { return true; }
	int GetDefense() const { return m_Defense; }

protected:
	int m_Defense;
};