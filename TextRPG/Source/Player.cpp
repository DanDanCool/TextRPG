#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::AddItem(Item* item)
{
	m_Inventory.push_back(item);
}

void Player::PopItem(Item* item)
{
	auto it = std::find(m_Inventory.begin(), m_Inventory.end(), item);
	if (it != m_Inventory.end())
	{
		if (item->IsEquippable())
			((WeaponItem*)item)->OnUnequip();
		m_Inventory.erase(it);
		delete item;
	}
}

void Player::UseItem(Item* item)
{
	ItemEffect effect = item->Use();

	for (int i = 0; i < effect.NumEffects; i++)
	{
		switch (*(effect.Actions + i))
		{
		case ItemAction::HealthIncrease:
			printf("You healed %i health!", *(effect.Effects + i));
			m_Health += *(effect.Effects + i);
			break;
		case ItemAction::StrengthIncrease:
			printf("You gained %i strength!", *(effect.Effects + i));
			m_Strength += *(effect.Effects + i);
			break;
		case ItemAction::DefenseIncrease:
			printf("You gained %i defense!", *(effect.Effects + i));
			m_Defense += *(effect.Effects + i);
			break;
		case ItemAction::Damage:
			printf("You stabbed yourself for %i damage!", *(effect.Effects + i));
			m_Health -= *(effect.Effects + i);
			break;
		}
	}
}

void Player::Equip(WeaponItem* item)
{
	if (m_Weapon)
		m_Weapon->OnUnequip();

	m_Weapon = item;
	item->OnEquip(this);
}

void Player::Equip(ArmorItem* item)
{
	if (m_Armor)
		m_Armor->OnUnequip();

	m_Armor = item;
	item->OnEquip(this);
}