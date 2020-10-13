#include "Item.h"

#include "../Random.h"
#include "../Util.h"

#include <stdio.h>


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
	int effects[] = { Util::Clamp(0, m_HealAmount + 4 * (Random::Float() - 0.5f)) };

	printf("You healed %i health!", effects[0]);

	return ItemEffect{ 1, actions, effects };
}

ItemEffect WeaponItem::Use()
{
	ItemAction actions[] = { ItemAction::Damage };
	int effects[] = { Util::Clamp(0, m_Damage + 10 * (Random::Float() - 0.f)) };

	printf("You took %i damage!", effects[0]);

	return ItemEffect{ 1, actions, effects };
}