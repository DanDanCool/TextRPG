#include "Item.h"

#include "../Random.h"
#include "../Util.h"

#include <stdio.h>


StatusEffect Item::Use()
{
	StatusAction actions = StatusAction::None;
	int effects = 0;
	
	return StatusEffect{ 1, &actions, &effects };
}

StatusEffect HealthItem::Use()
{
	StatusAction actions[] = { StatusAction::Health };
	int effects[] = { Util::Clamp(0, m_HealAmount + 4 * (Random::Float() - 0.5f)) };

	printf("You healed %d health!\n", effects[0]);

	return StatusEffect{ 1, actions, effects };
}

StatusEffect WeaponItem::Use()
{
	StatusAction actions = StatusAction::Health;
	int effects = -Util::Clamp(0, m_Damage + 10 * (Random::Float() - 0.f));

	printf("You took %d damage!\n", effects);

	return StatusEffect{ 1, &actions, &effects };
}