#include "DefenseItems.h"

#include "../Util.h"
#include <stdio.h>

AWoodenShield::AWoodenShield()
{
	m_Name = "Wooden Shield";
	m_Defense = 2;
}

AIronArmor::AIronArmor()
	: m_Name("Iron Armor"), m_Defense(5)
{
	m_Name = "Iron Armor";
	m_Defense = 5;
}

ADamascusSteelArmor::ADamascusSteelArmor()
{
	m_Name = "Damascus Steel Armor";
	m_Defense = 10;
}

AMysteriousRedAmulet::AMysteriousRedAmulet()
	: m_Defense(20)
{
	m_Name = Util::GetRandomName(6, true, "Mysterious Red Amulet");
	m_Defense = 20;
}

StatusEffect AMysteriousRedAmulet::OnUpdate()
{
	StatusAction actions = { StatusAction::HealthIncrease };
	int effects = { 2 };

	printf("Your red amulet shines vibrantly...\nYou gained 2 health!\n");

	return StatusEffect{ 1, actions, effects };
}