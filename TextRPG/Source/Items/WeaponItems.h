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

	virtual ItemEffect OnUnequip() override;
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

	virtual ItemEffect OnUnequip() override;
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

	virtual ItemEffect OnEquip() override;
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

	virtual ItemEffect OnUnequip() override;
};

class WDoubleSidedIronSword : public WeaponItem
{
public:
	WDoubleSidedIronSword();

	virtual ItemEffect OnUpdate() override;
};

class WLaserBlaster : public WeaponItem
{
	WLaserBlaster();

	virtual ItemEffect OnUpdate() override;
};

class WSharpestStick : public WeaponItem
{
	WSharpestStick();

	virtual ItemEffect OnUnequip() override;
};

class WMysteriousYellowAmulet : public WeaponItem
{
	WMysteriousYellowAmulet();

	virtual ItemEffect OnUnequip() override;
	virtual ItemEffect OnUpdate() override;
};