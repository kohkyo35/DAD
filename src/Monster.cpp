#include "Monster.h"
#include <iostream>
#include <cstdlib>
// ============================================================================
// Base Monster class
// ============================================================================

// TODO: Implement Monster constructor
// HINTS:
// - MUST call Character base constructor
// - Initialize experience_reward and gold_reward
// - Loot table starts empty automatically
//
Monster::Monster(const std::string& name, int hp, int attack, int defense,
                 int exp_reward, int gold_reward)
    : Character(name, hp, attack, defense),
      experience_reward(exp_reward), gold_reward(gold_reward) {
}


// TODO: Implement Monster destructor
// HINTS:
// - Deallocate any allocated memory 
// - Loop through loot_table vector and delete each Item*
// - Clear the vector after deleting items
//
Monster::~Monster() {
    for (size_t i = 0; i < loot_table.size(); i++) {
        delete loot_table[i];
    }
    loot_table.clear();
}


// TODO: Override displayStats
// HINTS:
// - Show monster name and HP
// - Format: "MonsterName [HP: current/max]"
// - Keep it simple - monsters don't need detailed stats display
//
void Monster::displayStats() const {
    // TODO: Display monster stats
    std::cout << getName() << " [HP: " << getCurrentHP() << "/" << getMaxHP() << "]" << std::endl;
}


// TODO: Implement addLoot
// HINTS:
// - Check if item pointer is not NULL
// - Add item to loot_table vector using push_back()
//
void Monster::addLoot(Item* item) {
    // TODO: Add item to loot table
        if (item != NULL) {
        loot_table.push_back(item);
    }//push_back vector adt 
}


// TODO: Implement dropLoot
// HINTS:
// - Create a copy of the loot_table vector
// - Clear the original loot_table (transfer ownership to caller!)
// - Return the copy
// - This is important: caller now owns the items and must delete them
//
std::vector<Item*> Monster::dropLoot() {
    // TODO: Return loot and transfer ownership
    std::vector<Item*> dropped = loot_table; // copy
    loot_table.clear();// transfer ownership
    return dropped;
    /*std::vector<Item*> empty;
    return empty;  // REPLACE THIS*/
}


// TODO: Implement getAttackMessage (base version)
// HINTS:
// - Return default attack message
// - Format: "MonsterName attacks!"
// - Use getName() to get monster's name
//
std::string Monster::getAttackMessage() const {
    // TODO: Return attack message
    return getName() + " attacks! BOOM!";
}


// ============================================================================
// Goblin - Weak but common enemy
// ============================================================================

// TODO: Implement Goblin constructor
// HINTS:
// - Call Monster constructor with these stats:
//   * Name: "Goblin"
//   * HP: 30
//   * Attack: 5
//   * Defense: 2
//   * Experience: 10
//   * Gold: 5
// - Add a small potion to loot table
// - Example: addLoot(new Consumable("Small Potion", "Restores 10 HP", 10));
//
Goblin::Goblin() 
    : Monster("Goblin", 30, 5, 2, 10, 5) {
    addLoot(new Consumable("Small Potion", "Restores 10 HP", 10));
    // TODO: Add loot items
}


// TODO: Override getAttackMessage for Goblin
// HINTS:
// - Return goblin-specific attack message
// - Example: "The goblin swipes at you with its rusty dagger!"
//
std::string Goblin::getAttackMessage() const {
    // TODO: Return goblin attack message
    return "The goblin swipes at you with its rusty dagger!";  // REPLACE THIS
}


// ============================================================================
// Skeleton - Undead warrior
// ============================================================================

// TODO: Implement Skeleton constructor
// HINTS:
// - Call Monster constructor with these stats:
//   * Name: "Skeleton"
//   * HP: 40
//   * Attack: 8
//   * Defense: 4
//   * Experience: 20
//   * Gold: 10
// - Add an old sword to loot table
//
Skeleton::Skeleton()
    : Monster("Skeleton", 40, 8, 4, 20, 10) {
        addLoot(new Weapon("Old Sword", "A worn-out sword", 3));
    // TODO: Add loot items
}


// TODO: Override getAttackMessage for Skeleton
// HINTS:
// - Return skeleton-specific attack message
// - Example: "The skeleton rattles its bones and slashes with a sword!"
//
std::string Skeleton::getAttackMessage() const {
    // TODO: Return skeleton attack message
    return "The skeleton rattles its bones and slashes with a sword!";  // REPLACE THIS
}


// ============================================================================
// Dragon - Boss enemy with special ability
// ============================================================================

// TODO: Implement Dragon constructor
// HINTS:
// - Call Monster constructor with these stats:
//   * Name: "Dragon"
//   * HP: 150
//   * Attack: 20
//   * Defense: 10
//   * Experience: 100
//   * Gold: 50
// - Add legendary loot:
//   * Dragon Slayer sword (damage +10)
//   * Dragon Scale Armor (defense +8)
//   * Greater Health Potion (heals 100 HP)
//
Dragon::Dragon()
    : Monster("Dragon", 150, 20, 10, 100, 50) {
        addLoot(new Weapon("Dragon Slayer", "A legendary sword", 10));
        addLoot(new Armor("Dragon Scale Armor", "Armor made from dragon scales", 8));
        addLoot(new Consumable("Greater Health Potion", "Restores 100 HP", 100));
    // TODO: Add legendary loot items
}


// TODO: Override getAttackMessage for Dragon
// HINTS:
// - Return dragon-specific attack message
// - Example: "The dragon breathes fire at you!"
//
std::string Dragon::getAttackMessage() const {
    // TODO: Return dragon attack message
    return "The dragon breathes fire at you!";  // REPLACE THIS
}


// TODO: Override calculateDamage for Dragon
// HINTS:
// - Call Monster::calculateDamage() to get base damage
// - Add bonus fire damage (+5)
// - Return total damage
// - This makes the dragon hit harder than other monsters!
//
int Dragon::calculateDamage() const {
    // TODO: Calculate damage with fire bonus
    int base = Monster::calculateDamage();
    return base + 5;  // REPLACE THIS
}
////////////////////////////EXTENSION 2
//ADDING NEW MONSTERS
//EXTENSION 2.1 TROLL

Troll::Troll() : Monster("Troll", 80, 2, 5, 30, 30){
    addLoot(new Consumable("Beef Sirloin", "Restores 30HP", 30)); // adding new consumable item to heal your hp by 30
}
std::string Troll::getAttackMessage() const {
    return "The troll attacks!";
}
///////////////2.2 GHOST with high evasion
Ghost::Ghost(): Monster("Ghost", 25, 10, 1, 25, 8)
{
    addLoot(new Consumable("Ghost Soul potion", "Restores 15HP", 15));
}
std::string Ghost::getAttackMessage() const {
    return "The ghost attacks!";
}
int Ghost::calculateDamage() const {// this is how i implemented evasion property of the ghost
    int roll = std::rand() % 10;
    if (roll < 10) {//adding chance of dodging ability
        return 0;
    }
    return Monster::calculateDamage();
}

Wizard::Wizard()
    : Monster("Wizard", 50, 12, 3, 40, 20)
{
    addLoot(new Consumable("Mana Potion", "Restores magical 30HP", 30));
    addLoot(new Weapon("Dumbledore's wand", "Wizard's heritage", 7));
}

std::string Wizard::getAttackMessage() const {
    return "The wizard attacks";
}

int Wizard::calculateDamage() const {
    int base = Monster::calculateDamage();
    return base + (std::rand() % 10);
}
