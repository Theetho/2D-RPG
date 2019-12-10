// Validate species : Human/Elf/Goblin --- Possible species : Centaur/Ghost/Giant/Trool or Troll/And all hybrid species 
/*
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Inventory.h"

class Character
{
public:
	Character();
    Character(std::string name, Sexe sexe, HairColor color, HairStyle style);
	virtual ~Character();

	// Displays informations about the character (@member[name], @member[level] and @member[healthPoints]) 
	void introduce() const;

	void gainEXP(long long EXPValue);
	void receiveDamage(int damageValue);
	void hitWithWeapon(Character &target) const;
	void pickUpItem(Item *item);
	void equipItem(Item *item);
	void displayInventory() const;

	// Getters 
	std::string GetName() const;
	Sexe GetSexe() const;
	int GetHealthPoints() const;
	int GetLevel() const;
	Inventory* GetInventory();

	// Setters 
	void SetName(std::string name);
	void SetSexe(Sexe sexe);
	void SetHair(HairColor color, HairStyle style);

protected:

    std::string name;
    Sexe sexe;
	Hair hair;
    Level level;
    HealthPoints healthPoints;
	Inventory inventory;	
};

#endif // _CHARACTER_H_
*/