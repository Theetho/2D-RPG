#include "stdafx.h"
#include "Macros.h"
#include "Character.h"
#include "Game.h"

using namespace sf;

int main()
{	
	/*
	 * ==================================================
	 * ================ SFML display ====================
	 * ==================================================
	 */
	Game game;

	game.Run();

	/*
	 * ==================================================
	 * ================ Terminal display ================
	 * ==================================================
	 */

	/*std::cout << "\n=== Beginning ===\n" << std::endl;

	Character mickael = Character();
	Character ahbdekha = Character("Ahbdekha", Sexe::MALE, HairColor::DARK, HairStyle::LONG);

	mickael.introduce();
	ahbdekha.introduce();

	std::cout << std::endl;
	std::cout << "=================" << std::endl << std::endl;

	Weapon wand("Shiny wand", ItemCategories::PRIMARY_WEAPON, WeaponCategories::WAND, 30);
	Weapon shield("Mighty shield", ItemCategories::SECONDARY_WEAPON, WeaponCategories::SHIELD, 10);
	Armor chest("Bright chest", ItemCategories::ARMOR, ArmorCategories::CHEST);
	Armor helmet("Coconut helmet", ItemCategories::ARMOR, ArmorCategories::HAT);

	ahbdekha.displayInventory();
	std::cout << "=================" << std::endl << std::endl;


	ahbdekha.pickUpItem(&wand);
	ahbdekha.pickUpItem(&shield);
	ahbdekha.pickUpItem(&chest);
	ahbdekha.pickUpItem(&helmet);
	std::cout << std::endl << "=================" << std::endl << std::endl;

	ahbdekha.displayInventory();
	std::cout << "=================" << std::endl << std::endl;

	ahbdekha.equipItem(&wand);
	ahbdekha.equipItem(&shield);
	ahbdekha.equipItem(&chest);
	ahbdekha.equipItem(&helmet);
	std::cout << std::endl << "=================" << std::endl << std::endl;

	ahbdekha.displayInventory();
	std::cout << "=================" << std::endl << std::endl;


	ahbdekha.hitWithWeapon(mickael);
	mickael.GetHealthPoints();
	std::cout << "=================" << std::endl << std::endl;

	mickael.gainEXP(450); // 5 148 376 331 max EXP;
	std::cout << std::endl << "=================" << std::endl << std::endl;

	std::cout << "\n=== End ===\n" << std::endl;

	system("PAUSE");*/

	return 0;
}

