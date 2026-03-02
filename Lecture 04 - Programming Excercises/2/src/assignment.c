///////////////////////////////////////////////////////////////////////////////
// In this C exercise, you will test some very basic
// C programming by implementing a small part of a 
// simple RPG combat system. 
// 
// Start simserver with a console connected as usual, 
// and try to pass all tests. 
//
// Do the assignments in order, as each assignment
// builds on the previous one.
///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

int hero_strength = 0; 
int hero_dexterity = 0;
int hero_weapon = 0; // 0 = unarmed, 1 = sword, 2 = axe, 3 = spear
int enemy_armour = 0; 

int enemy_defense()
{
    ///////////////////////////////////////////////////////////////////////////
    // Assignment 3: 
    // ====================================================
    // Enemy defense is enemy_armour * 2
    // Every time the hero attacks, the enemy's armour
    // is reduced by 1 (to a minimum of 0)
    ///////////////////////////////////////////////////////////////////////////
    int enemy_defense = enemy_armour * 2;
    if (enemy_armour > 0) {
        enemy_armour -= 1;
    }
    return enemy_defense; 
}

int weapon_bonus()
{
    ///////////////////////////////////////////////////////////////////////////
    // Assignment 2: 
    // ====================================================
    // Return weapon bonus based on hero_weapon value.
    //
    // unarmed = 0
    // sword = 5
    // axe = 7
    // spear = 6
    ///////////////////////////////////////////////////////////////////////////
    if (hero_weapon == 0) {
        return 0;
    }
    if (hero_weapon == 1) {
        return 5;
    }
    if (hero_weapon == 2) {
        return 7;
    }
    if (hero_weapon == 3) {
        return 6;
    }
    else return 0; 
}

int hero_damage()
{
    ///////////////////////////////////////////////////////////////////////////
    // Assignment 1: 
    // ====================================================
    // Calculate damage dealt in unarmed combat against
    // a monster without armour:
    // DAMAGE = STRENGTH * 2 + DEXTERITY + 
    //              (weapon_bonus() - enemy_armour())
    ///////////////////////////////////////////////////////////////////////////
    int damage = 0;
    damage = hero_strength * 2 + hero_dexterity + (weapon_bonus() - enemy_defense());
    return damage;    
}


/*
Testing assignment 1: Unarmed combat:
STR: 10 DEX: 5 => Damage: 25... PASS
STR: 2 DEX: 2 => Damage: 6... PASS
STR: 5 DEX: 8 => Damage: 18... PASS
STR: 0 DEX: 12 => Damage: 12... PASS
STR: 1 DEX: 20 => Damage: 22... PASS

Testing assignment 2: Armed combat:
STR: 10 DEX: 5 WEAPON: unarmed => Damage: 25 PASS
STR: 2 DEX: 2 WEAPON: sword => Damage: 11 PASS
STR: 5 DEX: 8 WEAPON: axe => Damage: 25 PASS
STR: 0 DEX: 12 WEAPON: spear => Damage: 18 PASS
STR: 1 DEX: 20 WEAPON: axe => Damage: 29 PASS

Testing assignment 3: Armed combat vs Armour:
STR: 10 DEX: 5 WEAPON: unarmed
ARMOUR: 10 => Damage: 15... FAIL (expected 5)
STR: 2 DEX: 2 WEAPON: sword
ARMOUR: 10 => Damage: 1... FAIL (expected -7)
STR: 5 DEX: 8 WEAPON: axe
ARMOUR: 10 => Damage: 15... FAIL (expected 9)
STR: 0 DEX: 12 WEAPON: spear
ARMOUR: 10 => Damage: 8... FAIL (expected 4)
STR: 1 DEX: 20 WEAPON: axe
ARMOUR: 10 => Damage: 19... FAIL (expected 17)

*/
