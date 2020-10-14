#pragma once

#include "Item.h"
#include "../Util.h"
#include <stdio.h>

class WWoodenSword : public WeaponItem
{
public:
	WWoodenSword();
};

class WThrowingRocks : public WeaponItem
{
public:
	WThrowingRocks();
};

class WAxe : public WeaponItem
{
public:
	WAxe();
};

class WStick : public WeaponItem
{
public:
	WStick();

	virtual StatusEffect OnUnequip() override;
};

class WStoneSword : public WeaponItem
{
public:
	WStoneSword();
};

class WBow : public WeaponItem
{
public:
	WBow();
};

class WBerserkerAxe : public WeaponItem
{
public:
	WBerserkerAxe();
};

class WSharpStick : public WeaponItem
{
public:
	WSharpStick();

	virtual StatusEffect OnUnequip() override;
};

class WIronSword : public WeaponItem
{
public:
	WIronSword();
};

class WGun : public WeaponItem
{
public:
	WGun();

	virtual StatusEffect OnEquip() override;
};


class WMadmanMachete : public WeaponItem
{
public:
	WMadmanMachete();
};


class WSharperStick : public WeaponItem
{
public:
	WSharperStick();

	virtual StatusEffect OnUnequip() override;
};

class WSwordOfSuperiority : public WeaponItem
{
public:
	WSwordOfSuperiority();

	virtual StatusEffect OnUpdate() override;
};

class WLaserBlaster : public WeaponItem
{
	WLaserBlaster();

	virtual StatusEffect OnUpdate() override;
};

class WSharpestStick : public WeaponItem
{
	WSharpestStick();

	virtual StatusEffect OnUnequip() override;
};

class WMysteriousYellowAmulet : public WeaponItem
{
	WMysteriousYellowAmulet();

	virtual StatusEffect OnUnequip() override;
	virtual StatusEffect OnUpdate() override;
};