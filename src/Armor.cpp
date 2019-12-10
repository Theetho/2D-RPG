#include "stdafx.h"
/*
#include "Macros.h"
#include "Item.h"
#include "Armor.h"

// Constructors
Armor::Armor() : Item(), armorCategory(ArmorCategories::NO_ARMOR)
{}

Armor::Armor(std::string name, ItemCategories category, ArmorCategories armorCategory) : Item(name, category), armorCategory(armorCategory)
{}

Armor::Armor(const Armor & armor)
{
	_name = armor.name;
	_category = armor.category;
	_armorCategory = armor.armorCategory;
}

// Destructor
Armor::~Armor()
{}

Armor & Armor::operator=(const Armor & armor)
{
	_name = armor.name;
	_category = armor.category;
	_armorCategory = armor.armorCategory;

	return *this;
}
// Getters
ArmorCategories Armor::GetArmorCategory() const
{
	return _armorCategory;
}

// ArmorCategory (string not enum [for display])
std::string Armor::showCategory() const
{
	switch (_armorCategory)
	{
		case ArmorCategories::NO_ARMOR:
			return "None";
			break;
		case ArmorCategories::HAT:
			return "Hat";
			break;
		case ArmorCategories::CLOAK:
			return "Cloak";
			break;
		case ArmorCategories::CHEST:
			return "Chest";
			break;
		case ArmorCategories::BELT:
			return "Belt";
			break;
		case ArmorCategories::PANTS:
			return "Pants";
			break;
		case ArmorCategories::BOOTS:
			return "Boots";
			break;
		case ArmorCategories::GLOVE_1:
			return "Gloves";
			break;
		case ArmorCategories::GLOVE_2:
			return "Gloves";
			break;
		case ArmorCategories::NECKLESS:
			return "Neckless";
			break;
		case ArmorCategories::EARING_1:
			return "Earings";
			break;
		case ArmorCategories::EARING_2:
			return "Earings";
			break;
		case ArmorCategories::RING_1:
			return "Ring";
			break;
		case ArmorCategories::RING_2:
			return "Ring";
			break;
		default:
			return "None";
			break;
	}
}
*/