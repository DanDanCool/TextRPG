#include "WeaponItems.h"

#include "../Util.h"
#include <stdio.h>

WWoodenSword::WWoodenSword()
{
	m_Name = "Wooden Sword";
	m_Damage = 3;
}

WThrowingRocks::WThrowingRocks()
{
	m_Name = "Throwing Rocks";
	m_Damage = 3;
}

WAxe::WAxe()
{
	m_Name = "Axe";
	m_Damage = 4;
}

WStick::WStick()
{
	m_Name = "Stick";
	m_Damage = 5;

}

ItemEffect WStick::OnUnequip()
{
	printf("You pricked yourself! You took some damage...");
	return WeaponItem::Use();
}

WStoneSword::WStoneSword()
{
	m_Name = "Stone Sword";
	m_Damage = 7;
}

WBow::WBow()
{
	m_Name = "Bow";
	m_Damage = 6
}

WBerserkerAxe::WBerserkerAxe()
{
	m_Name = "Berserker Axe";
	m_Damage = 10;
}

WSharpStick::WSharpStick()
{
	m_Name = "Sharp Stick";
	m_Damage = 11;

}

ItemEffect WSharpStick::OnUnequip()
{
	printf("You pricked yourself! You took some damage...");
	return WeaponItem::Use();
}

WIronSword::WIronSword()
{
	m_Name("Iron Sword";
	m_Damage = 15;
}

WGun::WGun()
{
	m_Name = "Gun";
	m_Damage = 17
}

ItemEffect WGun::OnEquip()
{
	printf("You equpped a gun and lost 5 defense!");
	ItemAction actions[] = { ItemAction::DefenseIncrease };
	int effects[] = { -5 };
	return ItemEffect{ 1, actions, effects };
}

WMadmanMachete::WMadmanMachete()
{
	m_Name = "Madman's Massacring Machete";
	m_Damage = 16;
}

WSharperStick::WSharperStick()
{
	m_Name = "Sharper Stick";
	m_Damage = 17;
}

ItemEffect WSharperStick::OnUnequip()
{
	printf("You pricked yourself! You took some damage...");
	return WeaponItem::Use();
}

WSwordOfSuperiority::WSwordOfSuperiority()
{
	m_Name = Util::GetRandomName(6, true, "'s Sword of Superiority");
	m_Damage = 17;
}

ItemEffect WSwordOfSuperiority::OnUpdate()
{
	ItemAction actions[] = { ItemAction::StrengthIncrease };
	int effects[] = { 20 };

	printf("You feel courage rushing through your veins\nStrength increased by 5");

	return ItemEffect{ 1, actions, effects };
}

WLaserBlaster::WLaserBlaster()
{
	m_Name = Util::GetRandomName(6, true, "'s Laser Blaster");
	m_Damage = 50;
}

ItemEffect WLaserBlaster::OnUpdate()
{
	ItemAction actions[] = { ItemAction::HealthIncrease, ItemAction::DefenseIncrease };
	int effects[] = { -5, -5 };

	printf("The radiation emitting from the Laser Blaster drains your health");
	printf("You took 5 damage! Defense decreased by 5");

	return ItemEffect{ 2, actions, effects };
}

WSharpestStick::WSharpestStick()
{
	m_Name = Util::GetRandomName(6, true, "'s Sharpest Stick");
	m_Damage = 30;
}

ItemEffect WSharpestStick::OnUnequip()
{
	printf("You pricked yourself! You took some damage...");
	return WeaponItem::Use();
}

WMysteriousYellowAmulet::WMysteriousYellowAmulet()
{
	m_Name = Util::GetRandomName(6, true, "'s Mysterious Yellow Amulet");
	m_Damage = 25;
}

ItemEffect WMysteriousYellowAmulet::OnUnequip()
{
	ItemAction actions = { ItemAction::HealthIncrease };
	int effects = { -100 };

	printf("You scream in agony as you try to wrench the amulet off...");
	printf("You lost 100 health");

	return ItemEffect{ 1, actions, effects };
}

ItemEffect WMysteriousYellowAmulet::OnUpdate()
{
	ItemAction actions = {
			ItemAction::HealthIncrease,
			ItemAction::StrengthIncrease,
			ItemAction::DefenseIncrease
	};

	int effects = { 5, 1, 2 };

	printf("Your yellow amulet glows mysteriously... You gained some stats!");
	printf("Health increased by 5! Strength increased by 1! Defense increased by 2!");

	return ItemEffect{ 3, actions, effects };
}