#include "DefenseItems.h"

#include "../Util.h"
#include <stdio.h>

AWoodenShield::AWoodenShield()
{
	m_Name = "Wooden Shield";
	m_Defense = 20;
}

AIronArmor::AIronArmor()
{
	m_Name = "Iron Armor";
	m_Defense = 50;
}

ADamascusSteelArmor::ADamascusSteelArmor()
{
	m_Name = "Damascus Steel Armor";
	m_Defense = 120;
}

AMysteriousRedAmulet::AMysteriousRedAmulet()
{
	m_Name = Util::GetRandomName(6, true, "'s Mysterious Red Amulet");
	m_Defense = 300;
}

StatusEffect AMysteriousRedAmulet::OnUpdate()
{
	StatusAction actions = StatusAction::Health;
	int effects = 20;

	printf("Your red amulet shines vibrantly...\nYou gained 20 health!\n");

	StatusEffect statusEffect;
	statusEffect.Size = 1;
	statusEffect.Actions = &actions;
	statusEffect.Effects = &effects;

	return statusEffect;
}