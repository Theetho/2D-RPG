#include "stdafx.h"
/*
#include "Macros.h"
#include "Inventory.h"

// Constructors
Inventory::Inventory() : hand_1(0), hand_2(0), bag(0), stuff(0), size(15), firstFreeSlot(0)
{
	_hand_1 = new Weapon("Grandma's wand", ItemCategories::PRIMARY_WEAPON, WeaponCategories::WAND, 10);
	_hand_2 = new Weapon("Wooden shield", ItemCategories::SECONDARY_WEAPON, WeaponCategories::SHIELD, 5);

	_stuff = new Armor*[static_cast<int>(ArmorCategories::RING_2)];
	_bag = new Item*[_size];

	for (int i = 0; i < static_cast<int>(ArmorCategories::RING_2); i++)
	{
		_stuff[i] = nullptr;
	}
	for (int i = 0; i < _size; i++)
	{
		_bag[i] = nullptr;
	}
}

Inventory::Inventory(std::string primaryWeaponName, ItemCategories primaryWeaponCategory, 
					 WeaponCategories weaponCategory, int primaryWeaponDamage) : hand_1(0), hand_2(0), bag(0), stuff(0), size(15), firstFreeSlot(0)
{
	_hand_1 = new Weapon(primaryWeaponName, primaryWeaponCategory, weaponCategory, primaryWeaponDamage);
	_hand_2 = new Weapon("Wooden shield", ItemCategories::NO_ITEM, WeaponCategories::SHIELD, 5);

	_stuff = new Armor*[static_cast<int>(ArmorCategories::RING_2)];
	_bag = new Item*[_size];

	for (int i = 0; i < static_cast<int>(ArmorCategories::RING_2); i++)
	{
		_stuff[i] = nullptr;
	}
	for (int i = 0; i < _size; i++)
	{
		_bag[i] = nullptr;
	}
};

// Destructor
Inventory::~Inventory()
{
	delete _hand_1;
	delete _hand_2;
	delete _bag;
	delete _stuff;
}

// Returns FALSE if a slot is available in the bag and Set the firstFreeIndex if so.
bool Inventory::isFull()
{
	for (int i = 0; i < _size; i++)
	{
		if (!_bag[i])
		{
			_firstFreeSlot = i;
			return false;
		}
	}
	return true;
}

void Inventory::removeFromBag(Item * item)
{
	for (int i = 0; i < _size; i++)
	{
		if (_bag[i] == item)
		{
			_bag[i] = nullptr;
			break;
		}
	}
}

void Inventory::removeFromStuff(Item * item)
{
	if (!isFull())
	{
		_bag[_firstFreeSlot] = item;
		_stuff[static_cast<int>(item->GetCategory())] = nullptr;
	}
	else
	{
		// Nothing for now
		return;
	}
}

// Check if the item is in the bag and if so, returns its index in the bag, else return -1
int Inventory::isInBag(Item * item)
{
	for (int i = 0; i < _size; i++)
	{
		if (_bag[i] == item)
		{
			return i;
		}
	}
	return -1;
}

// Getters
Weapon* Inventory::GetWeapon_1() const
{
	return _hand_1;
}

Weapon* Inventory::GetWeapon_2() const
{
	return _hand_2;
}

Item ** Inventory::GetBag() const
{
	return _bag;
}

Armor ** Inventory::GetStuff() const
{
	return _stuff;
}

int Inventory::GetSize() const
{
	return _size;
}

// Setters
// Puts the item in the bag if it is not full
void Inventory::SetBag(Item * item)
{
	if (!isFull())
	{
		_bag[_firstFreeSlot] = item;
	}
	else
	{
		std::cout << "Bag is full" << std::endl;
	}
}

// Equips the weapon in primary hand
void Inventory::SetWeapon_1(Weapon * weapon)
{	
	// If there is already a weapon in the primary_hand
	if (_hand_1)
	{
		// Check if it was an invalid weapon, and if so, puts the weapon in the slot
		if (_hand_1->GetCategory() == ItemCategories::NO_ITEM)
		{
			*_hand_1 = *weapon;
		}
		// Else it switches both weapons (weapon goes in the stuff and the previous weapon goes in the bag)
		else
		{
			int index = isInBag(weapon);
			if (index >= 0)
			{
				SWAP_VALUE(_hand_1, weapon);
			}
		}
	}
	// Else the slot is free, so it puts the armor in the stuff (and remove it from bag)
	else
	{
		_hand_2 = weapon;
		int index = isInBag(weapon);
		if (index >= 0)
		{
			_bag[index] = nullptr;
		}
	}
}

// Equips the weapon in secondary hand
void Inventory::SetWeapon_2(Weapon * weapon)
{
	// Same as SetWeapon_1
	if (_hand_2)
	{
		if (_hand_2->GetCategory() == ItemCategories::NO_ITEM)
		{
			*_hand_2 = *weapon;
		}
		else
		{
			int index = isInBag(weapon);
			if (index >= 0)
			{
				SWAP_VALUE(_hand_2, weapon);
			}
		}
	}
	else
	{
		_hand_2 = weapon;
		int index = isInBag(weapon);
		if (index >= 0)
		{
			_bag[index] = nullptr;
		}
	}
}

// Equips the item
void Inventory::SetStuff(Armor *armor)
{
	// If there is already an armor in that slot
	if (_stuff[static_cast<int>(armor->GetArmorCategory())])
	{
		// Check if it was an invalid armor
		if (_stuff[static_cast<int>(armor->GetArmorCategory())]->GetCategory() == ItemCategories::NO_ITEM)
		{
			*_stuff[static_cast<int>(armor->GetArmorCategory())] = *armor;
		}
		// Else it switches both armors (armor goes in the stuff and the previous armor goes in the bag)
		else
		{
			int index = isInBag(armor);
			if (index >= 0)
			{
				SWAP_VALUE(_stuff[static_cast<int>(armor->GetArmorCategory())], armor);
			}
		}
	}
	// Else the slot is free, so it puts the armor in the stuff (and remove it from bag)
	else
	{
		_stuff[static_cast<int>(armor->GetArmorCategory())] = armor;
		int index = isInBag(armor);
		if (index >= 0)
		{
			_bag[index] = nullptr;
		}
	}
}

*/