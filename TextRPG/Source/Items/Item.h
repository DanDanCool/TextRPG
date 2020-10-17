#pragma once

//items return a StatusEffect object to interact with the player
#include "../StatusEffect.h"

/*
 * Item is a special type of class, called a virtual class. You cannot create virtual classes,
 * but you can have pointers of them. Like so:
 * Item* myPtr = nullptr;
 * The reason why this works is because myPtr is actually pointing to an object that isn't an
 * Item.
 * 
 * C++ is object oriented, which means it supports inheritance an polymorphism, let me walk you
 * through what this means.
 * 
 * You can inherit a class's methods and variables, this adds all its methods and variables to the
 * class you defined, see HealthItem below for an example.
 * In addition, inheritance adds another property to your class, polymorphism. HealthItem can be
 * interpreted as both the type 'HealthItem' and 'Item.'
 *
 * This fact is used in the Player inventory, since all classes that inherit from Item can be
 * interpreted as an item, we can store a heterogenous array of them.
 */

//virtual class, cannot be instantiated as its methods aren't defined
class Item
{
public:
	virtual ~Item() = default;

	virtual StatusEffect Use();
	virtual bool IsEquippable() { return false; }

	const char* GetName() const { return m_Name; }

//protected is like private, but subclasses can access the methods and variables
protected:
	//makes it so that Item can't be instantiated
	Item() = default;
	
	const char* m_Name;
};

//HealthItem is a 'concrete' class, which means it provides definitions for all of its methods
//and can be instantiated
class HealthItem : public Item
{
public:
	virtual StatusEffect Use() override;
	bool IsEquippable() final { return false; }

protected:
	int m_HealAmount = 0;
};

//EquippableItem is another virtual class, it provides default implementation for all methods, so
//it technically can be used, but this is not intended behavior, so the constructor is marked as
//protected
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