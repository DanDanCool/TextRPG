#pragma once

class Player;

enum class ItemAction
{
	None = 0,
	HealthIncrease,
	StrengthIncrease,
	DefenseIncrease,
	Damage
};

struct ItemEffect
{
	int NumEffects;
	ItemAction* Actions;
	int* Effects;
};

class Item
{
public:
	virtual ~Item() = default;

	virtual ItemEffect Use();
	virtual bool IsEquippable() { return false; }

protected:
	Item() = default;
};

class HealthItem : public Item
{
public:
	virtual ItemEffect Use() override;
	bool IsEquippable() final { return false; }

protected:
	int m_HealAmount = 0;
};

class EquippableItem : public Item
{
public:
	virtual ItemEffect OnEquip() { return Item::Use(); }
	virtual ItemEffect OnUnequip() { return Item::Use(); }

	virtual ItemEffect OnUpdate() { return Item::Use(); }

	bool IsEquippable() final { return true; }

	virtual bool IsWeapon() { return false; }
	virtual bool IsArmor() { return false; }

protected:
	EquippableItem() = default;
};

class WeaponItem : public EquippableItem
{
public:
	virtual ItemEffect Use() override;
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