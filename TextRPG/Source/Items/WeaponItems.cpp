#include "WeaponItems.h"

#include "../Util.h"
#include <stdio.h>

WWoodenSword::WWoodenSword()
{
	m_Name = "Wooden Sword";
	m_Damage = 8;
}

WThrowingRocks::WThrowingRocks()
{
	m_Name = "Throwing Rocks";
	m_Damage = 8;
}

WAxe::WAxe()
{
	m_Name = "Axe";
	m_Damage = 14;
}

WStick::WStick()
{
	m_Name = "Stick";
	m_Damage = 15;

}

StatusEffect WStick::OnUnequip()
{
	printf("You pricked yourself! You took some damage...\n");
	return WeaponItem::Use();
}

WStoneSword::WStoneSword()
{
	m_Name = "Stone Sword";
	m_Damage = 23;
}

WBow::WBow()
{
	m_Name = "Bow";
	m_Damage = 20;
}

WBerserkerAxe::WBerserkerAxe()
{
	m_Name = "Berserker Axe";
	m_Damage = 24;
}

WSharpStick::WSharpStick()
{
	m_Name = "Sharp Stick";
	m_Damage = 27;

}

StatusEffect WSharpStick::OnUnequip()
{
	printf("You pricked yourself! You took some damage...\n");
	return WeaponItem::Use();
}

WIronSword::WIronSword()
{
	m_Name = "Iron Sword";
	m_Damage = 40;
}

WGun::WGun()
{
	m_Name = "Gun";
	m_Damage = 50;
}

StatusEffect WGun::OnEquip()
{
	printf("You equpped a gun and lost 15 defense!\n");

	StatusAction actions[] = { StatusAction::Defense };
	int effects[] = { -15 };
	
	StatusEffect statusEffect;
	statusEffect.Size = 1;
	statusEffect.Actions = actions;
	statusEffect.Effects = effects;

	return statusEffect;
}

WMadmanMachete::WMadmanMachete()
{
	m_Name = "Madman's Massacring Machete";
	m_Damage = 38;
}

WSharperStick::WSharperStick()
{
	m_Name = "Sharper Stick";
	m_Damage = 45;
}

StatusEffect WSharperStick::OnUnequip()
{
	printf("You pricked yourself! You took some damage...\n");
	return WeaponItem::Use();
}

WSwordOfSuperiority::WSwordOfSuperiority()
{
	m_Name = Util::GetRandomName(6, true, "'s Sword of Superiority");
	m_Damage = 100;
}

StatusEffect WSwordOfSuperiority::OnUpdate()
{
	StatusAction actions[] = { StatusAction::Strength };
	int effects[] = { 100 };

	printf("You feel courage rushing through your veins...\nStrength increased by 100!\n");

	StatusEffect statusEffect;
	statusEffect.Size = 1;
	statusEffect.Actions = actions;
	statusEffect.Effects = effects;

	return statusEffect;
}

WLaserBlaster::WLaserBlaster()
{
	m_Name = Util::GetRandomName(6, true, "'s Laser Blaster");
	m_Damage = 10000000;
}

StatusEffect WLaserBlaster::OnUpdate()
{
	StatusAction actions[] = { StatusAction::Health, StatusAction::Defense };
	int effects[] = { -100, -100 };

	printf("The radiation emitting from the Laser Blaster drains your health...\n");
	printf("You took 100 damage! Defense decreased by 100!\n");

	StatusEffect statusEffect;
	statusEffect.Size = 2;
	statusEffect.Actions = actions;
	statusEffect.Effects = effects;

	return statusEffect;
}

WSharpestStick::WSharpestStick()
{
	m_Name = Util::GetRandomName(6, true, "'s Sharpest Stick");
	m_Damage = 200;
}

StatusEffect WSharpestStick::OnUnequip()
{
	printf("You pricked yourself! You took some damage...\n");
	return WeaponItem::Use();
}

WMysteriousYellowAmulet::WMysteriousYellowAmulet()
{
	m_Name = Util::GetRandomName(6, true, "'s Mysterious Yellow Amulet");
	m_Damage = 150;
}

StatusEffect WMysteriousYellowAmulet::OnUnequip()
{
	StatusAction actions = StatusAction::Health;
	int effects = -100 ;

	printf("You scream in agony as you try to wrench the amulet off...\n");
	printf("You lost 100 health!\n");

	StatusEffect statusEffect;
	statusEffect.Size = 1;
	statusEffect.Actions = &actions;
	statusEffect.Effects = &effects;

	return statusEffect;
}

StatusEffect WMysteriousYellowAmulet::OnUpdate()
{
	StatusAction actions[] = { StatusAction::Health, StatusAction::Strength, StatusAction::Defense };
	int effects[] = { 50, 10, 20 };

	printf("Your yellow amulet glows mysteriously... You gained some stats!\n");
	printf("Health increased by 50! Strength increased by 10! Defense increased by 20!\n");

	StatusEffect statusEffect;
	statusEffect.Size = 3;
	statusEffect.Actions = actions;
	statusEffect.Effects = effects;

	return statusEffect;
}