#include "Character.h"
#include <cstdlib>

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
    return 0;  // REPLACE THIS
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
}


// TODO: Implement displayStats
// HINTS:
// - Print character name and HP
// - Format: "Name [HP: current/max]"
// - This is the default implementation - derived classes can override
//
void Character::displayStats() const {
    // TODO: Print character stats
}


// TODO: Implement displayStatus
// HINTS:
// - Brief one-line status (used during combat)
// - Don't add newline at the end (combat system will add it)
// - Format: "Name [HP: current/max]"
//
void Character::displayStatus() const {
    // TODO: Print brief status
}
