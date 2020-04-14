#include "stdafx.h"
/* 
#include "Macros.h"
#include "Character.h"

// Constructors
Character::Character() : name("Mickael"), sexe(Sexe::MALE), hair{ HairColor::DARK, HairStyle::SHORT }, level{ 1, 0, 300 }, healthPoints{ 100, 100, 0, 0 }, inventory()
{}

Character::Character(std::string name, Sexe sexe, HairColor color, HairStyle style)
					: name(name), sexe(sexe), hair{ color, style }, level{ 1, 0, 300 }, 
					  healthPoints{ 100, 100, 0, 0 }, inventory()
{}

// Destructor 
Character::~Character() 
{}

// Removes DamageValue to the character's health points 
void Character::receiveDamage(int damageValue)
{
	std::cout << _name << " loses " << damageValue << " health points." << std::endl;
	
	_healthPoints.currentHealthPoints -= damageValue;
	// Check that HPs dont go below 0
	if (_healthPoints.currentHealthPoints < 0)
	{
		_healthPoints.currentHealthPoints = 0;
	}
}

// Attacks the target with the weapon that has the higher damages 
void Character::hitWithWeapon(Character &target) const
{
	// Select the best weapon 
	Weapon *weapon = IF_MAX(_inventory.GetWeapon_1()->GetDamage(), _inventory.GetWeapon_2()->GetDamage(), _inventory.GetWeapon_1(), _inventory.GetWeapon_2());
	std::cout << _name << " hits " << target.name << " with " << GENDER(_sexe, "his ", "her ") << weapon->GetName() << "." << std::endl;

	target.receiveDamage(weapon->GetDamage());
}

// Puts an item in the character's inventory if it is not full 
void Character::pickUpItem(Item * item)
{
	std::cout << _name << " picks up \"" << item->GetName() << "\"." << std::endl;
	
	_inventory.SetBag(item);
}

// Equips an item depending on its category 
void Character::equipItem(Item * item)
{
	std::cout << _name << " equips \"" << item->GetName() << "\"." << std::endl;
	
	if (item->GetCategory() == ItemCategories::PRIMARY_WEAPON)
		_inventory.SetWeapon_1(dynamic_cast<Weapon*>(item));
	else if (item->GetCategory() == ItemCategories::SECONDARY_WEAPON)
		_inventory.SetWeapon_2(dynamic_cast<Weapon*>(item));
	else
		_inventory.SetStuff(dynamic_cast<Armor*>(item));
}

// DEBUG FUNCTION : just display what is inside the character's inventory 
void Character::displayInventory() const
{
	std::cout << _name << "'s inventory : " << std::endl << std::endl << "Bag : [";

	// Display items in bag 
	for (int i = 0; i < _inventory.GetSize(); i++)
	{
		if (_inventory.GetBag()[i])
			std::cout << _inventory.GetBag()[i]->GetName() << "//";
		else
			std::cout << "..." << "//";
	}

	std::cout << "]" << std::endl << "      [";

	// Display the item's category
	for (int i = 0; i < _inventory.GetSize(); i++)
	{
		if (_inventory.GetBag()[i] != nullptr)
		{
			std::cout << _inventory.GetBag()[i]->showCategory();

			for (int j = 0; j < _inventory.GetBag()[i]->GetName().size() - _inventory.GetBag()[i]->showCategory().size(); j++)
			{
				std::cout << " ";
			}
			std::cout << "//";
		}
		else
			std::cout << "..." << "//";
	}

	std::cout << "]" << std::endl << std::endl << "Stuff : [";
	
	for (int i = 0; i < static_cast<int>(ArmorCategories::RING_2); i++)
	{
		if (_inventory.GetStuff()[i] != nullptr)
			std::cout << _inventory.GetStuff()[i]->GetName() << "//";
		else
			std::cout << "..." << "//";
	}
	std::cout << "]" << std::endl << "        [";
	for (int i = 0; i < static_cast<int>(ArmorCategories::RING_2); i++)
	{
		if (_inventory.GetStuff()[i] != nullptr)
		{
			std::cout << _inventory.GetStuff()[i]->showCategory();
			for (int j = 0; j < _inventory.GetStuff()[i]->GetName().size() - _inventory.GetStuff()[i]->showCategory().size(); j++)
			{
				std::cout << " ";
			}
			std::cout << "//";
		}
		else
			std::cout << "..." << "//";
	}
	std::cout << "]" << std::endl << std::endl << "Weapon : - Primary weapon : ";
	if (_inventory.GetWeapon_1() != nullptr)
		std::cout << _inventory.GetWeapon_1()->GetName() << " (" << _inventory.GetWeapon_1()->showCategory() << ", " << _inventory.GetWeapon_1()->GetDamage() << PLURAL(_inventory.GetWeapon_1()->GetDamage(), " damages)", " damage)") << std::endl;
	else
		std::cout << " None" << std::endl;
	if (_inventory.GetWeapon_2() != nullptr)
		std::cout << "         - Secondary weapon : " << _inventory.GetWeapon_2()->GetName() << " (" << _inventory.GetWeapon_2()->showCategory() << ", " << _inventory.GetWeapon_2()->GetDamage() << PLURAL(_inventory.GetWeapon_2()->GetDamage(), " damages)", " damage)") << std::endl << std::endl;
	else
		std::cout << " None" << std::endl << std::endl;
}

std::string Character::GetName() const
{
	std::cout << "Your character is called " << _name << std::endl;
	return _name;
}

Sexe Character::GetSexe() const
{
	std::cout << _name << " is a ";
	std::cout << GENDER(_sexe, "man ", "woman ") << std::endl;
	return _sexe;
}

int Character::GetHealthPoints() const
{
	std::cout << _name << " has " << _healthPoints.currentHealthPoints << "/" << _healthPoints.characteristicHealthPoint + _healthPoints.equipmentHealthPoints + _healthPoints.levelHealthPoints << " health points." << std::endl;
	return _healthPoints.currentHealthPoints;
}

int Character::GetLevel() const
{
	std::cout << _name << " is level " << _level.level << ". ";
	std::cout << GENDER(_sexe, "his", "her") << "experience is " << _level.currentLevelEXP << "/" << _level.nextLevelEXP << std::endl;
	return _level.level;
}

Inventory* Character::GetInventory()
{
	return &(_inventory);
}

void Character::SetName(std::string name)
{
	std::cout << _name << " will be called " << name << " from now." << std::endl;
	_name = name;
}

void Character::SetSexe(Sexe sexe)
{
	std::cout << _name << " is now a ";
	std::cout << GENDER(_sexe, "man ", "woman ") << std::endl;
	_sexe = sexe;
}

void Character::SetHair(HairColor color, HairStyle style)
{
	_hair.color = color;
	_hair.style = style;
}
*/