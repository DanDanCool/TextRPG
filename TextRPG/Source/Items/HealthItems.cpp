#include "HealthItems.h"

#include "../Util.h"
#include <stdio.h>

HBandage::HBandage()
{
	m_Name = "Bandage";
	m_HealAmount = 5;
}

HFish::HFish()
{
	m_Name = "Fish";
	m_HealAmount = 3;
}

ItemEffect HFish::Use()
{
	ItemAction actions[] = { ItemAction::HealthIncrease, ItemAction::StrengthIncrease };
	int effects[] = { m_HealAmount, 1 };

	printf("You ate a fish!\nYou gain 3 health and 1 strength!");

	return ItemEffect{ 2, actions, effects };
}

HHamburger::HHamburger()
{
	m_Name = "Hamburger";
	m_HealAmount = 5;
}

HHealingPotion::HHealingPotion()
{
	m_Name = "Healing Potion";
	m_HealAmount = 10;
}

HElixirOfLongevity::HElixirOfLongevity()
{
	m_Name = "Elixir of Longevity";
	m_HealAmount = 11;
}

HSuperFish::HSuperFish()
{
	m_Name = "Super Fish";
	m_HealAmount = 7;
}

HSuperFish::Use()
{
	ItemAction actions[] = { ItemAction::HealthIncrease, ItemAction::StrengthIncrease };
	int effects[] = { m_HealAmount, 4 };

	printf("You eat a super fish!\nYou gain 7 health and 4 strength");

	return ItemEffect{ 2, actions, effects };
}

HGreaterHealingPotion::HGreaterHealingPotion()
{
	m_Name = "Greater Healing Potion";
	m_HealAmount = 15;
}

HGreaterElixirOfLongevity::HGreaterElixirOfLongevity()
{
	m_Name = "Greater Elixir of Longevity";
	m_HealAmount = 17;
}

HSupererFish::HSupererFish()
{
	m_Name = "Superer Fish";
	m_HealAmount = 12;

}

ItemEffect HSupererFish::Use()
{
	ItemAction actions = { ItemAction::HealthIncrease, ItemAction::StrengthIncrease, ItemAction::DefenseIncrease };
	int effects = { m_HealAmount, 8, 2 };

	printf("You ate a superer fish!\nHealth increased by 12! Strength increased by 8! Defense increased by 2!");

	return ItemEffect{ 3, actions, effects };
}

HSupremeHealingPotion::HSupremeHealingPotion()
{
	m_Name = Util::GetRandomName(6, true, "'s Supreme Healing Potion");
	m_HealAmount = 20;
}

HSupremeElixirOfLongevity::HSupremeElixirOfLongevity()
{
	m_Name = Util::GetRandomName(6, true, "'s Supreme Elixir of Longevity");
	m_HealAmount = 22;
}

ItemEffect HSupremeElixirOfLongevity::Use()
{
	ItemAction actions[] = { ItemAction::HealthIncrease, ItemAction::DefenseIncrease };
	int effects = { m_HealAmount, 10 };

	printf("You drink the Supreme Elixir of Longevity...\nHealth increased by 22! Defense Increased by 10!");

	return ItemEffect{ 2, actions, effects };
}

HSupremeFish::HSupremeFish()
{
	m_Name = Util::GetRandomName(6, true, "'s Supreme Fish");
	m_HealAmount = 14;
}

ItemEffect HSupremeFish::Use()
{
	ItemAction actions[] = {
			ItemAction::HealthIncrease,
			ItemAction::StrengthIncrease,
			ItemAction::DefenseIncrease
	};

	int effects = { m_HealAmount, 20, 20 };

	printf("You eat the supreme fish...\nHealth increased by 14! Strength increased by 20! Defense increased by 20!");

	return ItemEffect{ 3, actions, effects };
}