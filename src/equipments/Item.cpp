#include "stdafx.h"
/*
#include "Macros.h"
#include "Item.h"

// Constructors
Item::Item() : name("NULL"), category(ItemCategories::NO_ITEM)
{}

Item::Item(std::string name, ItemCategories category) : name(name), category(category)
{}

Item::Item(const Item & item)
{
	_category = item.category;
	_name = item.name;
}

// Destructor
Item::~Item()
{}

Item & Item::operator=(const Item & item)
{
	_category = item.category;
	_name = name;

	return *this;
}

// Getters
std::string Item::GetName() const
{
	return _name;
}

ItemCategories Item::GetCategory() const
{
	return _category;
}

// Category (string not enum [for display])
std::string Item::showCategory() const
{
	switch (_category)
	{
	case ItemCategories::NO_ITEM:
		return "None";
		break;
	case ItemCategories::ARMOR:
		return "Armor";
		break;
	case ItemCategories::PRIMARY_WEAPON:
		return "Primary Weapon";
		break;
	case ItemCategories::SECONDARY_WEAPON:
		return "Secondary Weapon";
		break;
	default:
		return "None";
		break;
	}
}
*/