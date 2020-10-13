#pragma once

#include "Item.h"

class HBandage : public HealthItem
{
public:
	HBandage();
};

class HFish : public HealthItem
{
public:
	HFish();

	virtual ItemEffect Use() override;
};

class HHamburger : public HealthItem
{
public:
	HHamburger();
};

class HHealingPotion : public HealthItem
{
public:
	HHealingPotion();
};

class HElixirOfLongevity : public HealthItem
{
public:
	HElixirOfLongevity();
};

class HSuperFish : public HealthItem
{
public:
	HSuperFish();

	virtual ItemEffect Use() override;
};

class HGreaterHealingPotion : public HealthItem
{
public:
	HGreaterHealingPotion();
};

class HGreaterElixirOfLongevity : public HealthItem
{
public:
	HGreaterElixirOfLongevity();
};

class HSupererFish : public HealthItem
{
public:
	HSupererFish();

	virtual ItemEffect Use() override;
};

class HSupremeHealingPotion : public HealthItem
{
public:
	HSupremeHealingPotion();
};

class HSupremeElixirOfLongevity : public HealthItem
{
public:
	HSupremeElixirOfLongevity();

	virtual ItemEffect Use() override;
};

class HSupremeFish : public HealthItem
{
public:
	HSupremeFish();

	virtual ItemEffect Use() override;
};