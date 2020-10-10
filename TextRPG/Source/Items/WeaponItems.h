#pragma once

#include "Item.h"

class WWoodenSword : public WeaponItem
{
public:
	WWoodenSword()
		: m_Damage(3) {}
};

class WThrowingRocks : public WeaponItem
{
public:
	WThrowingRocks()
		: m_Damage(2) {}
};

class WAxe : public WeaponItem
{
public:
	WAxe()
		: m_Damage(4) {}
};

class WStick : public WeaponItem
{
public:
	WStick()
		: m_Damage(5) {}
};

class WStoneSword : public WeaponItem
{
public:
	WStoneSword()
		: m_Damage(7) {}
};

class WBow : public WeaponItem
{
public:
	WBow()
		: m_Damage(6) {}
};

class WBerserkerAxe : public WeaponItem
{
public:
	WBerserkerAxe()
		: m_Damage(10) {}
};

class WSharpStick : public WeaponItem
{
public:
	WSharpStick()
		: m_Damage(11) {}
};

class WIronSword : public WeaponItem
{
public:
	WIronSword()
		: m_Damage(15) {}
};

damageitems3 = ["Iron Sword", "Gun", "Madman's Massacring Machete", "Sharper Stick"]
damageitems4 = ["Double Sided Iron Sword", "Laser Blaster", "Sharpest Stick", "Mysterious Yellow Amulet"]