#ifndef _MACROS_H_
#define _MACROS_H_

/*
 * ==================================================
 * =================== Macros =======================
 * ==================================================
 */

#define GENDER(sexe, maleAction, femaleAction) ((sexe == Sexe::MALE) ? maleAction : femaleAction)
#define PLURAL(x, plural, singular) ((x>1) ? plural : singular)
#define IF_MIN(x, y, ifX, ifY) ((x<y) ? ifX : ifY)
#define IF_MAX(x, y, ifX, ifY) ((x>y) ? ifX : ifY)

/*
 * ==================================================
 * ================== Templates =====================
 * ==================================================
 */

template<typename T>
void SWAP_POINTERS(T* x, T* y)
{
	T *tmp = x;
	x = y;
	y = tmp;

	return x;
}
template<typename T>
void SWAP_VALUE(T* x, T* y)
{
	T tmp = *x;
	*x = *y;
	*y = tmp;
}

/*
 * ==================================================
 * ================= Enumeration ====================
 * ==================================================
 */

enum class ItemCategories { ARMOR, PRIMARY_WEAPON, SECONDARY_WEAPON, NO_ITEM,};
enum class WeaponCategories { WAND, STAFF, MAGIC_RING, SHIELD, NO_WEAPON};
enum class ArmorCategories { HAT, CLOAK, CHEST, BELT, PANTS, BOOTS, GLOVE_1, GLOVE_2, NECKLESS, EARING_1, EARING_2, RING_1, RING_2, NO_ARMOR };
enum class Sexe { MALE, FEMALE };
enum class AnimationSide { LEFT, RIGHT, DOWN, UP };
enum class Menu { NONE, MAIN_MENU, PAUSE_MENU, CHARACTER_MENU };
enum class WhichState { NONE, GAME_STATE, MENU_STATE, EDITOR_STATE };
enum class TransitionStatus { NONE, HALF, WAIT_COMPLETE, COMPLETE };
#endif // !_MACROS_H_
