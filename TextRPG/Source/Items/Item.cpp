#include "Item.h"

#include "../Random.h"

#include <stdio.h>

static int Clamp(int min, int value) {
	return value > min ? value : min;
}

ItemEffect Item::Use()
{
	printf("Nothing happened");

	ItemAction actions[] = { ItemAction::None };
	int effects[] = { 0 };
	
	return ItemEffect{ 1, actions, effects };
}

ItemEffect HealthItem::Use()
{
	ItemAction actions[] = { ItemAction::HealthIncrease };
	int effects[] = { Clamp(0, m_HealAmount + 4 * (Random::Float() - 0.5f)) };

	return ItemEffect{ 1, actions, effects };
}

ItemEffect WeaponItem::Use()
{
	ItemAction actions[] = { ItemAction::Damage };
	int effects[] = { Clamp(0, m_Damage + 10 * (Random::Float() - 0.f)) };

	return ItemEffect{ 1, actions, effects };
}