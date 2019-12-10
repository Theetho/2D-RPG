/*
#ifndef _WEAPON_H_
#define _WEAPON_H_

class Weapon : public Item
{
public:
	Weapon();
	Weapon(std::string name, ItemCategories category, WeaponCategories weaponCategory, int damage);
	Weapon(const Weapon &weapon);
	virtual ~Weapon();

	Weapon &operator=(const Weapon &weapon);

	// Getters
	int GetDamage() const;
	virtual WeaponCategories GetWeaponCategory() const;
	virtual std::string showCategory() const;

private:
	int damage;
	WeaponCategories weaponCategory;
};

#endif // !_WEAPON_H_
*/