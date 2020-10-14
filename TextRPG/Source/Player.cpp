#include "Player.h"
#include "Util.h"

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

bool Player::HasItem(Item* item) const
{
	auto it = std::find(m_Inventory.begin(), m_Inventory.end(), item);
	if (it != m_Inventory.end())
		return true;

	return false;
}

void Player::UseItem(Item* item)
{
	if (HasItem(item))
	{
		StatusEffect effect = item->Use();
		HandleStatusEffect(effect);

		if (item != m_Weapon || item != m_Armor)
		{
			PopItem(item);
			delete item;
		}
	}
}

void Player::Equip(WeaponItem* item)
{
	StatusEffect effect;
	if (m_Weapon)
	{
		effect = m_Weapon->OnUnequip();
		HandleStatusEffect(effect);
	}

	m_Weapon = item;
	effect = item->OnEquip(this);
	HandleStatusEffect(effect);
}

void Player::Equip(ArmorItem* item)
{
	StatusEffect effect;

	if (m_Armor)
	{
		effect = m_Armor->OnUnequip();
		HandleStatusEffect(effect);
	}

	m_Armor = item;
	effect = item->OnEquip(this);
	HandleStatusEffect(effect);
}

bool Player::IsWeaponEquipped() const
{
	if (m_Weapon)
		return true;
	
	return false;
}

bool Player::IsArmorEquipped() const
{
	if (m_Armor)
		return true;
	
	return false;
}

void Player::HandleStatusEffect(const StatusEffect& effect)
{
	for (int i = 0; i < effect.Size; i++)
	{
		switch (*(effect.Actions + i))
		{
		case StatusAction::Health:
			m_Health += *(effect.Effects + i);
			if (m_Health < 0)
				m_bAlive = true;
			break;
		case StatusAction::Strength:
			m_Strength += *(effect.Effects + i);
			m_Strength = Util::Clamp(0, m_Strength);
			break;
		case StatusAction::Defense:
			m_Defense += *(effect.Effects + i);
			m_Defense = Util::Clamp(0, m_Defense);
			break;
		}
	}
}