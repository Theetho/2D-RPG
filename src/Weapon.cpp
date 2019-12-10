#include "stdafx.h"
/*
#include "Macros.h"
#include "Item.h"
#include "Weapon.h"

// Constructors
Weapon::Weapon() : Item(), weaponCategory(WeaponCategories::NO_WEAPON), damage(0)
{}

Weapon::Weapon(std::string name, ItemCategories category, WeaponCategories weaponCategory, int damage) : Item(name, category), weaponCategory(weaponCategory), damage(damage)
{}

Weapon::Weapon(const Weapon & weapon)
{
	_category = weapon.category;
	_name = weapon.name;
	_damage = weapon.damage;
	_weaponCategory = weapon.weaponCategory;
}

// Destructors
Weapon:: ~Weapon()
{}

Weapon & Weapon::operator=(const Weapon &weapon)
{
	_category = weapon.category;
	_name = weapon.name;
	_damage = weapon.damage;
	_weaponCategory = weapon.weaponCategory;

	return *this;
}

// Getters
int Weapon::GetDamage() const
{
	return _damage;
}

WeaponCategories Weapon::GetWeaponCategory() const
{
	return _weaponCategory;
}

// WeaponCategory (string not enum [for display])
std::string Weapon::showCategory() const
{
	switch (_weaponCategory)
	{
	case WeaponCategories::NO_WEAPON:
		return "None";
		break;
	case WeaponCategories::WAND:
		return "Wand";
		break;
	case WeaponCategories::STAFF:
		return "Staff";
		break;
	case WeaponCategories::MAGIC_RING:
		return "Magic ring";
		break;
	case WeaponCategories::SHIELD:
		return "Shield";
		break;
	default:
		return "None";
		break;
	};
}
*/