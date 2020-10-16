#include "Player.h"
#include "Util.h"

Player::Player()
{

}

Player::~Player()
{
	delete[] m_Name;
}

void Player::Reset()
{
	m_Inventory.clear();

	m_Weapon = nullptr;
	m_Armor = nullptr;

	delete[] m_Name;
	m_Name = nullptr;

	m_bAlive = true;

	m_Health = 20;
	m_Defense = 10;
	m_Strength = 15;
	m_Money = 30;
}

void Player::OnUpdate()
{
	if (m_Weapon)
	{
		auto statusEffect = m_Weapon->OnUpdate();
		HandleStatusEffect(statusEffect);
	}

	if (m_Armor)
	{
		auto statusEffect = m_Armor->OnUpdate();
		HandleStatusEffect(statusEffect);
	}
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

		if (item == m_Weapon)
		{
			auto effect = m_Weapon->OnUnequip();
			HandleStatusEffect(effect);

			m_Weapon = nullptr;
		}
		else if (item == m_Armor)
		{
			auto effect = m_Weapon->OnUnequip();
			HandleStatusEffect(effect);

			m_Armor = nullptr;
		}

		m_Inventory.erase(it);
		delete item;
	}
}

void Player::PopItem(const char* name)
{
	for (auto* item : m_Inventory)
	{
		if (!strcmp(item->GetName(), name))
		{
			PopItem(item);
			return;
		}
	}

	printf("Poor input.");
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
		if (item->IsEquippable())
		{
			if (((EquippableItem*)item)->IsArmor())
				Equip((ArmorItem*)item);
			else
				Equip((WeaponItem*)item);

			return;
		}

		StatusEffect effect = item->Use();
		HandleStatusEffect(effect);

		PopItem(item);
		delete item;
	}
}

void Player::UseItem(const char* name)
{
	for (auto* item : m_Inventory)
	{
		if (!strcmp(item->GetName(), name))
		{
			if (item->IsEquippable())
			{
				if (((EquippableItem*)item)->IsArmor())
					Equip((ArmorItem*)item);
				else
					Equip((WeaponItem*)item);

				return;
			}

			StatusEffect effect = item->Use();
			HandleStatusEffect(effect);

			PopItem(item);
		}
	}

	printf("Poor input.");
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
	effect = item->OnEquip();
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
	effect = item->OnEquip();
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
				m_bAlive = false;
			break;
		case StatusAction::Strength:
			m_Strength += *(effect.Effects + i);
			m_Strength = Util::Clamp(0, m_Strength);
			break;
		case StatusAction::Defense:
			m_Defense += *(effect.Effects + i);
			m_Defense = Util::Clamp(0, m_Defense);
			break;
		case StatusAction::Money:
			m_Money += *(effect.Effects + i);
			break;
		}
	}
}

int Player::GetDefense() const
{
	if (m_Armor)
		return m_Defense + m_Armor->GetDefense();

	return m_Defense;
}

int Player::GetDamage() const
{
	if (m_Weapon)
		return m_Strength + m_Weapon->GetDamage();

	return m_Strength;
}
