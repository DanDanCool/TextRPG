#include "Shop.h"

#include "Items/HealthItems.h"
#include "Items/WeaponItems.h"
#include "Items/DefenseItems.h"

#include "Random.h"

#include <vector>

static constexpr int HEALTH_ITEMS1[] = {
	0, //HBandage
	1, //HFish
	2  //HHamburger
};

static constexpr int HEALTH_ITEMS2[] = {
	3, //HHealingPotion
	4, //HElixirOfLongevity
	5  //HSuperFish
};

static constexpr int HEALTH_ITEMS3[] = {
	6, //HGreaterHealingPotion
	7, //HGreaterElixirOfLongevity
	8  //HSupererFish
};

static constexpr int HEALTH_ITEMS4[] = {
	9,  //HSupremeHealingPotion
	10, //HSupremeElixirOfLongevity
	11  //HSupremeFish
};

static constexpr int WEAPON_ITEMS1[] = {
	12, //WWoodenSword
	13, //WThrowingRocks
	14, //WAxe
	15  //WStick
};

static constexpr int WEAPON_ITEMS2[] = {
	16, //WStoneSword
	17, //WBow
	18, //WBerserkerAxe
	19  //WSharpStick
};

static constexpr int WEAPON_ITEMS3[] = {
	20, //WIronSword
	21, //WGun
	22, //WMadmanMachete
	23  //WSharperStick
};

static constexpr int WEAPON_ITEMS4[] = {
	24, //WSwordOfSuperiority
	25, //WLaserBlaster
	26, //WSharpestStick
	27  //WMysteriousYellowAmulet
};

static constexpr int DEFENSE_ITEMS[] = {
	28, //AWoodenShield
	29, //AIronArmor
	30, //ADamascusSteelArmor
	31  //AMysteriousRedAmulet
};

static constexpr const char* SKILL_ITEMS1[] = {
	"Point Booster",
	"Skill of Bribery",
	"Skill of Charm",
	"Skill of Begging"
};

static constexpr const char* SKILL_ITEMS2[] = {
	"Super Point Booster",
	"Skill of Thievery",
	"Skill of Manipulation",
	"Skill of Desperation"
};

static constexpr const char* SKILL_ITEMS3[] = {
	"Ultra Point Booster",
	"Skill of Piracy",
	"Skill of Extortion",
	"Skill of Politics"
};

static constexpr const char* SKILL_ITEMS4[] = {
	"Super Ultra Mega Point Boosterino",
	"Skill of Swashbuckling",
	"Skill of Domination",
	"Mysterious Green Amulet"
};

static Item* CreateItem(uint32_t item)
{
	switch (item)
	{
		case 0:  return new HBandage();
		case 1:  return new HFish();
		case 2:  return new HHamburger();
		case 3:  return new HHealingPotion();
		case 4:  return new HElixirOfLongevity();
		case 5:  return new HSuperFish();
		case 6:  return new HGreaterHealingPotion();
		case 7:  return new HGreaterElixirOfLongevity();
		case 8:  return new HSupererFish;
		case 9:  return new HSupremeHealingPotion();
		case 10: return new HSupremeElixirOfLongevity();
		case 11: return new HSupremeFish();
		case 12: return new WWoodenSword();
		case 13: return new WThrowingRocks();
		case 14: return new WAxe();
		case 15: return new WStick();
		case 16: return new WStoneSword();
		case 17: return new WBow();
		case 18: return new WBerserkerAxe();
		case 19: return new WSharpStick();
		case 20: return new WIronSword();
		case 21: return new WGun();
		case 22: return new WMadmanMachete();
		case 23: return new WSharperStick();
		case 24: return new WSwordOfSuperiority();
		case 25: return new WLaserBlaster();
		case 26: return new WSharpestStick();
		case 27: return new WMysteriousYellowAmulet();
		case 28: return new AWoodenShield();
		case 29: return new AIronArmor();
		case 30: return new ADamascusSteelArmor();
		case 31: return new AMysteriousRedAmulet();
	}
}

Shop CreateShop(int step)
{
	if (step >= 40)
		return CreateShop1();
	if (step >= 80)
		return CreateShop2();
	if (step >= 120)
		return CreateShop3();
	if (step >= 160)
		return CreateShop4();
}

Shop CreateShop1()
{
	Shop shop;

	for (int i = 0; i < 4; i++)
		shop.Costs[i] = 40 - Random::UInt32(0, 20);

	shop.HealthItem = CreateItem(HEALTH_ITEMS1[Random::UInt32(0, 2)]);
	shop.WeaponItem = CreateItem(WEAPON_ITEMS1[Random::UInt32(0, 3)]);
	shop.ArmorItem = CreateItem(DEFENSE_ITEMS[0]);

	shop.ScoreItemName = SKILL_ITEMS1[Random::UInt32(0, 3)];

	return shop;
}

Shop CreateShop2()
{
	Shop shop;

	for (int i = 0; i < 4; i++)
		shop.Costs[i] = 80 - Random::UInt32(0, 30);

	shop.HealthItem = CreateItem(HEALTH_ITEMS2[Random::UInt32(0, 2)]);
	shop.WeaponItem = CreateItem(WEAPON_ITEMS2[Random::UInt32(0, 3)]);
	shop.ArmorItem = CreateItem(DEFENSE_ITEMS[1]);

	shop.ScoreItemName = SKILL_ITEMS2[Random::UInt32(0, 3)];

	return shop;
}

Shop CreateShop3()
{
	Shop shop;

	for (int i = 0; i < 4; i++)
		shop.Costs[i] = 120 - Random::UInt32(0, 40);

	shop.HealthItem = CreateItem(HEALTH_ITEMS3[Random::UInt32(0, 2)]);
	shop.WeaponItem = CreateItem(WEAPON_ITEMS3[Random::UInt32(0, 3)]);
	shop.ArmorItem = CreateItem(DEFENSE_ITEMS[2]);

	shop.ScoreItemName = SKILL_ITEMS2[Random::UInt32(0, 3)];

	return shop;
}

Shop CreateShop4()
{
	Shop shop;

	for (int i = 0; i < 4; i++)
		shop.Costs[i] = 500 - Random::UInt32(0, 100);

	shop.HealthItem = CreateItem(HEALTH_ITEMS4[Random::UInt32(0, 2)]);
	shop.WeaponItem = CreateItem(WEAPON_ITEMS4[Random::UInt32(0, 3)]);
	shop.ArmorItem = CreateItem(DEFENSE_ITEMS[3]);

	shop.ScoreItemName = SKILL_ITEMS4[Random::UInt32(0, 3)];

	return shop;
}