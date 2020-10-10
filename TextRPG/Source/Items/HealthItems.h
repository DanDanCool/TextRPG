#pragma once

#include "Item.h"

class HBandage : public HealthItem
{
public:
	HBandage()
		: m_HealAmount(5) {}
};

class HFish : public HealthItem
{
public:
	HFish()
		: m_HealAmount(3) {}

	virtual ItemEffect Use() override
	{
		ItemAction actions[] = { ItemAction::HealthIncrease, ItemAction::StrengthIncrease };
		int effects[] = { m_HealAmount, 1 };
		return ItemEffect{ 2, actions, effects };
	}
};

class HHamburger : public HealthItem
{
public:
	HHamburger()
		: m_HealAmount(5) {}
};

class HHealingPotion : public HealthItem
{
public:
	HHealingPotion()
		: m_HealAmount(10) {}
};

class HElixirOfLongevity : public HealthItem
{
public:
	HElixirOfLongevity()
		: m_HealAmount(11) {}
};

class HSuperFish : public HealthItem
{
public:
	HSuperFish()
		: m_HealAmount(7) {}

	virtual ItemEffect Use() override
	{
		ItemAction actions[] = { ItemAction::HealthIncrease, ItemAction::StrengthIncrease };
		int effects[] = { m_HealAmount, 4 };
		return ItemEffect{ 2, actions, effects };
	}
};

class HGreaterHealingPotion : public HealthItem
{
public:
	HGreaterHealingPotion()
		: m_HealAmount(15) {}
};

class HGreaterElixirOfLongevity : public HealthItem
{
public:
	HGreaterElixirOfLongevity()
		: m_HealAmount(17) {}
};

class HSupererFish : public HealthItem
{
public:
	HSupererFish()
		: m_HealAmount(12) {}

	virtual ItemEffect Use() override
	{
		ItemAction actions = { ItemAction::HealthIncrease, ItemAction::StrengthIncrease, ItemAction::DefenseIncrease };
		int effects = { m_HealAmount, 8, 2 };
		return ItemEffect{ 3, actions, effects };
	}
};

class HSupremeHealingPotion : public HealthItem
{
public:
	HSupremeHealingPotion()
		: m_HealAmount(20) {}
};

class HSupremeElixirOfLongevity : public HealthItem
{
public:
	HSupremeElixirOfLongevity()
		: m_HealAmount(22) {}

	virtual ItemEffect Use() override
	{
		ItemAction actions[] = { ItemAction::HealthIncrease, ItemAction::DefenseIncrease };
		int effects = { m_HealAmount, 10 };
		return ItemEffect{ 2, actions, effects };
	}
};

class HSupremeFish : public HealthItem
{
public:
	HSupremeFish()
		: m_HealAmount(14) {}

	virtual ItemEffect Use() override
	{
		ItemAction actions[] = { ItemAction::HealthIncrease, ItemAction::StrengthIncrease, ItemAction::DefenseIncrease };
		int effects = { m_HealAmount, 20, 20 };
		return ItemEffect{ 3, actions, effects };
	}
};