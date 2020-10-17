/*
 * I forgot to mention this before... oh well
 * 
 * There are two stages when building a project, a compilation stage and the linking stage. The
 * compilation stage was explained before, to summarize, the compiler compiles all of your .cpp
 * files into assembly code, MSVC stores them in .obj files.
 * You typically include a lot of header files, but those (typically) only have declarations, no
 * definitions, how then, does the translation unit know how to call that function?
 * The answer is in the second stage of building a project, the linking stage. The linker links
 * functions calls to the translation units they're defined in, and produces a binary output,
 * such as a .exe, .dll, or .lib.
 * 
 * Naturally, there are two types of errors, compiler errors and linking errors. Compiler errors
 * tell you that you have incorrect syntax or something, and the compiler can't generate correct
 * code. Linking errors are a bit harder to debug, usually it's an error with duplicate definitions
 * (remember that C++ has a one definition rule), or with no definition at all.
 * 
 * This article gives an excellent explanation for further reading:
 * https://stackoverflow.com/questions/6264249/how-does-the-compilation-linking-process-work
 * Remember stackoverflow... you'll be using it a lot
 */

#include "Player.h"

//utility functions
#include "Util.h"

Player::Player()
{

}

Player::~Player()
{
	//see comment in Player::Reset, just deletes the items in the inventory
	for (Item* item : m_Inventory)
		delete item;

	//The name was allocated on the stack in Game::Start, so it must be deleted, I am aware this is
	//pretty terrible
	delete[] m_Name;
}

//reset the player stats
void Player::Reset()
{
	/*
	 * The clear function that std::vector provides does not free the memory the pointers are pointing
	 * to, so it must be deleted manually.
	 * 
	 * Modern C++ provides a new way to iterate through objects through a 'for each' type of for loop.
	 * Which is being used here.
	 */

	for (Item* item : m_Inventory)
		delete item;

	//clear the inventory, clear is a function std::vector provides
	m_Inventory.clear();

	m_Weapon = nullptr;
	m_Armor = nullptr;

	/*
	 * This is a situation where using raw deletes might get a bit confusing, if you're not careful
	 * you may crash your program by freeing memory that doesn't belong to you.
	 * 
	 * For example, what if the player is reset, and then destroyed? m_Name would get deleted twice,
	 * causing a crash. But the execution of the program does not allow this, so this never happens.
	 * In a more complicated program, it is more difficult to trace (predict) how the program will
	 * run, so raw deletes like this may cause crashes.
	 */

	delete[] m_Name;
	m_Name = nullptr;

	m_bAlive = true;

	m_Health = 20;
	m_Defense = 10;
	m_Strength = 15;
	m_Money = 30;
}

//on update
void Player::OnUpdate()
{
	//when evaluated as a boolean, nullptr will be evaluated to false, pointers are 64 bit memory
	//addresses, so if they point to something, they won't be 0, and will evaluate to true
	if (m_Weapon)
	{
		/*
		 * Sometimes the compiler can deduce the type of a variable for you, which can save you from
		 * typing something, this should only be used when it enhance readability, as it actually
		 * makes it harder to see what type the variable is.
		 * The type of statusEffect is StatusEffect, this name is pretty short and the code would be
		 * better if it was used.
		 * This was definitely done on purpose for demonstration and not becuase I was lazy.
		 */

		auto statusEffect = m_Weapon->OnUpdate();
		HandleStatusEffect(statusEffect);
	}

	if (m_Armor)
	{
		auto statusEffect = m_Armor->OnUpdate();
		HandleStatusEffect(statusEffect);
	}
}

//add an item to the player's inventory
void Player::AddItem(Item* item)
{
	//push_back is a function in std::vector that adds something to the ending of the vector
	//when this is called, the vector checks if it has enough space, if not, it resizes itself
	//by allocating twice it's current memory and copying everyting over to the new memory
	//this gets pretty slow so be sure to size your vectors appropirately
	m_Inventory.push_back(item);
}

//delete an item from the player's inventory
void Player::PopItem(Item* item)
{
	//it is an iterator of type std::vector<Item*>::iterator, this is where the use of auto is
	//actually justified
	
	//std::find just finds an element in an array and returns an iterator pointing to that location
	auto it = std::find(m_Inventory.begin(), m_Inventory.end(), item);

	//std::find will return std::vector<>.end() if it cannot find a value, this is not a valid element
	//in the array
	if (it != m_Inventory.end())
	{
		//check if the item is the weapon the player is holding
		if (item == m_Weapon)
		{
			//again, bad use of auto
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
		
		//remove the item from the vector
		m_Inventory.erase(it);

		//free the memory
		delete item;
	}
}

//proxy function that takes in a string
void Player::PopItem(const char* name)
{
	for (auto* item : m_Inventory)
	{
		//if the names are equal, delete the item
		if (!strcmp(item->GetName(), name))
		{
			//calls PopItem to delete the item, technically it searches twice which is inefficient
			//but whatever
			PopItem(item);

			//we don't need to continue looping so we return
			return;
		}
	}

	//the string was not matched to anything
	printf("Poor input.");
}

//check if the player has an item, it is marked as const as it does not modify the player
bool Player::HasItem(Item* item) const
{
	auto it = std::find(m_Inventory.begin(), m_Inventory.end(), item);
	if (it != m_Inventory.end())
		return true;

	return false;
}

//use an item
void Player::UseItem(Item* item)
{
	if (HasItem(item))
	{
		//equip the item, note that this makes the item's 'use' function uselesss
		if (item->IsEquippable())
		{
			/*
			 * Memory does not inherently have a 'type,' this is a term we give it to make data
			 * easier to work with. Technically, this cast is a bit dangerous, but we do check
			 * if the item is of type 'EquippapleItem' by asking if it's equippable, and then
			 * cast it to the 'EquippableItem' type, more about this in Item.h where polymorphism
			 * is explained.
			 */

			if (((EquippableItem*)item)->IsArmor())
				Equip((ArmorItem*)item);

			//must be a WeaponItem, still a bit dangerous
			else
				Equip((WeaponItem*)item);

			//we don't want to delete the item, so we skip the code below
			return;
		}

		StatusEffect effect = item->Use();
		HandleStatusEffect(effect);

		//most items are one time use, so they get deleted on use
		PopItem(item);
		delete item;
	}
}

//same things as above but with strings
void Player::UseItem(const char* name)
{
	for (auto* item : m_Inventory)
	{
		//this is defined again here to remove the need of searching twice as with PopItem
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

	//item not found
	printf("Poor input.");
}

//equip an item
void Player::Equip(WeaponItem* item)
{
	//the weapon sends a StatusEffect object when it is equipped, it is handled here

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

/*
 * In C++, you can have multiple functions with the same name, the compiler will deduce which function
 * to call at compile time. This is called function overloading. However, there are limitations, your
 * functions must have different function signatures. A function's signature is it's name plus it's
 * parameters. If the compiler can't deduce which function to call, it gives a compiler error.
 */

void Player::Equip(ArmorItem* item)
{
	//same with above

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

//returns if the weapon is equipped by checking if the weapon is a nullptr
bool Player::IsWeaponEquipped() const
{
	if (m_Weapon)
		return true;
	
	return false;
}

//returns if armor is equipped by checking if the armor is a nullptr
bool Player::IsArmorEquipped() const
{
	if (m_Armor)
		return true;
	
	return false;
}

/*
 * Why is the parameter const StatusEffect& instead of StatusEffect? By default, C++ copies the object
 * by value, this may be slow for large objects, so we pass an object by reference, that is, pass the
 * object's memory address to the function. It is marked as const because we do not modify it.
 */

//code for handling status effects
void Player::HandleStatusEffect(const StatusEffect& effect)
{
	/*
	 * StatusEffect has two pointers to the start of two arrays, to support variable length arrays,
	 * StatusEffect also has a Size attribute with the number of elements in both arrays.
	 * 
	 * Notice how we don't access each member of the array with the [] operator. This can be done
	 * because arrays are stored contiguously in memory.
	 * 
	 * For example, if we wanted to access the second element in an array called 'myArray,' we could do
	 * it like so:
	 * 
	 * int myArray[10];
	 * *(myArray + 1) = //something here;
	 * 
	 * By default, using 'myArray' actually returns a pointer to the first element in the array (myArray[0]).
	 * 
	 * So we just increment the memory addresses to access all of the elements in the array.
	 * The elements are accessed by dereferencing the pointer.
	 */

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
			//clamp the strength to be 0, negative strength doesn't really make sense
			m_Strength = Util::Clamp(0, m_Strength);
			break;
		case StatusAction::Defense:
			m_Defense += *(effect.Effects + i);
			//same with strength
			m_Defense = Util::Clamp(0, m_Defense);
			break;
		case StatusAction::Money:
			m_Money += *(effect.Effects + i);
			break;
		}
	}
}

//get the player defense
int Player::GetDefense() const
{
	//check if the armor exists, if m_Armor is a nullptr, and GetDefense is called on it
	//the program will crash
	if (m_Armor)
		return m_Defense + m_Armor->GetDefense();

	return m_Defense;
}

int Player::GetDamage() const
{
	//same with above
	if (m_Weapon)
		return m_Strength + m_Weapon->GetDamage();

	return m_Strength;
}
