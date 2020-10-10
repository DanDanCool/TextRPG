#pragma once

#include "Item.h"

class AWoodenShield : public ArmorItem
{
public:
	AWoodenShield()
		: m_Defense(2) {}
};

class AIronArmor : public ArmorItem
{
public:
	AIronArmor()
		: m_Defense(5) {}
};

class ADamascusSteelArmor : public ArmorItem
{
public:
	ADamascusSteelArmor()
		: m_Defense(10) {}
};

class AMysteriousRedAmulet : public ArmorItem
{
public:
	AMysteriousRedAmulet()
		: m_Defense(20) {}

	virtual ItemEffect OnUpdate() override
	{
		ItemAction actions = { ItemAction::HealthIncrease };
		int effects = { 2 };
		return ItemEffect{ 1, actions, effects };
	}
};