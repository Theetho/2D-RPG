/*
#ifndef _ARMOR_H_
#define _ARMOR_H_

class Armor : public Item
{
public:
	Armor();
	Armor(std::string name, ItemCategories category, ArmorCategories weaponCategory);
	Armor(const Armor &armor);
	virtual ~Armor();

	Armor &operator=(const Armor &armor);

	// Getters
	ArmorCategories GetArmorCategory() const;
	std::string showCategory() const;

private:
	ArmorCategories armorCategory;
};

#endif // !_ARMOR_H_

*/

