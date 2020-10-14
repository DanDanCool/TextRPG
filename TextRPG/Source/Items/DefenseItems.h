#pragma once

#include "Item.h"

class AWoodenShield : public ArmorItem
{
public:
	AWoodenShield();
};

class AIronArmor : public ArmorItem
{
public:
	AIronArmor();
};

class ADamascusSteelArmor : public ArmorItem
{
public:
	ADamascusSteelArmor();
};

class AMysteriousRedAmulet : public ArmorItem
{
public:
	AMysteriousRedAmulet();

	virtual StatusEffect OnUpdate() override;
};