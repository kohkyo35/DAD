#include "Character.h"
#include <cstdlib>
#include <iostream>

// TODO: Implement Character constructor
// HINTS:
// - Use initializer list to initialize all member variables
// - Set current_hp to hp (start at full health)
// - Set alive to true (character starts alive)
// - Format: Character::Character(params) : member1(value1), member2(value2) { }
//
Character::Character(const std::string& name, int hp, int attack, int defense)
    : name(name), max_hp(hp), current_hp(hp), attack(attack), 
      defense(defense), alive(true) {
}


// TODO: Implement Character destructor
// HINTS:
// - For base Character class, clean up any dynamic resources if needed
// - You can add a debug print statement if helpful for tracking object lifetime
// - Example: std::cout << "Character " << name << " destroyed" << std::endl;
//
Character::~Character() {
}


// TODO: Implement calculateDamage
// HINTS:
// - Return attack damage plus a random bonus (0-4)
// - Use: rand() % 5 to get random number from 0 to 4
//
int Character::calculateDamage() const {
    // TODO: Calculate and return damage
    // Base damage is attack stat plus small random bonus
    return attack + (rand() % 5);
}


// TODO: Implement takeDamage
// HINTS:
// - Reduce damage by defense value (actual_damage = damage - defense)
// - Make sure actual damage is not negative (minimum 0)
// - Subtract actual damage from current_hp
// - If hp drops to 0 or below: set hp to 0 and set alive to false
// - Print damage message showing damage taken and remaining HP
// - Format: "Name takes X damage! (Y/Z HP)"
//
void Character::takeDamage(int damage) {
    // TODO: Calculate actual damage after defense
    // TODO: Apply damage to current_hp
    // TODO: Check if character died (hp <= 0)
    // TODO: Print damage message with remaining HP
    //damage reduced by defense and the minimum it can take is 0
    int actual = damage - defense;
    if (actual < 0) actual = 0;
    //Applying Damage when hp is below 0 you're dead so change the alive status to false
    current_hp -= actual;
    if(current_hp <= 0){
        current_hp = 0;
        alive = false;
    }
    std::cout << name << " takes " << actual << " damage! (" 
              << current_hp << "/" << max_hp << " HP)" << std::endl;
}


// TODO: Implement heal
// HINTS:
// - Add healing amount to current_hp
// - Make sure current_hp doesn't exceed max_hp (cap at maximum)
// - Print healing message showing amount healed and current HP
// - Format: "Name heals X HP! (Y/Z HP)"
//
void Character::heal(int amount) {
    // TODO: Add amount to current_hp
    // TODO: Cap at max_hp
    // TODO: Print healing message
    current_hp += amount;
    if (current_hp > max_hp) current_hp = max_hp;


    std::cout << name << " heals " << amount << " HP! ("
              << current_hp << "/" << max_hp << " HP)" << std::endl;
}


// TODO: Implement displayStats
// HINTS:
// - Print character name and HP
// - Format: "Name [HP: current/max]"
// - This is the default implementation - derived classes can override
//
void Character::displayStats() const {
    // TODO: Print character stats
    std::cout << name << " [HP: " << current_hp << "/" << max_hp << "]" << std::endl;
}


// TODO: Implement displayStatus
// HINTS:
// - Brief one-line status (used during combat)
// - Don't add newline at the end (combat system will add it)
// - Format: "Name [HP: current/max]"
//
void Character::displayStatus() const {
    std::cout << name << " [HP: " << current_hp << "/" << max_hp << "]";
}