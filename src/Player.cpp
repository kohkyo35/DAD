#include "Player.h"
#include <iostream>
#include <algorithm>

// TODO: Implement Player constructor
// HINTS:
// - MUST call Character base constructor. 
//
Player::Player(const std::string& name)
    : Character(name, 100, 10, 5),
      level(1), experience(0), gold(0),
      equipped_weapon(NULL), equipped_armor(NULL) {
}
//inheritance aplied where player is the child of Character class

// TODO: Implement Player destructor
// HINTS:
// - CRITICAL: Must delete all items in inventory to prevent memory leaks!
// - DON'T delete equipped_weapon or equipped_armor - they point to items
//   already in the inventory, so they're already deleted!
//
Player::~Player() {
    // TODO: Delete all inventory items
    for (size_t i = 0; i < inventory.size(); i++) {
        delete inventory[i];
    }
    inventory.clear();
}


// TODO: Override displayStats
// HINTS:
// - Show player-specific information
// - Include: level, HP, attack (with weapon bonus), defense (with armor bonus), gold, experience
// - Show equipped weapon and armor names if any
// - Use decorative formatting (borders, headers)
// - Use getters to access inherited Character data
//
void Player::displayStats() const {
    // TODO: Display comprehensive player stats
    std::cout << "=====================" << std::endl;
    std::cout << getName() << " - Level " << level << std::endl;
    std::cout << "HP: " << getCurrentHP() << "/" << getMaxHP() << std::endl;

    int atk = getAttack();
    int def = getDefense();

    //static_cast<data type>(parameter) meaning that change the type of equipped_weapon to Weapon*
    //use static_cast to access getDamageBonus and getDefenseBonus because equipped_weapon is Item* data type
    
    if (equipped_weapon) atk += static_cast<Weapon*>(equipped_weapon)->getDamageBonus();
    if (equipped_armor) def += static_cast<Armor*>(equipped_armor)->getDefenseBonus();


    std::cout << "Attack: " << atk;
    if (equipped_weapon) std::cout << " (" << equipped_weapon->getName() << ")";
    std::cout << std::endl;

    std::cout << "Defense: " << def;
    if (equipped_armor) std::cout << " (" << equipped_armor->getName() << ")";
    std::cout << std::endl;

    std::cout << "Gold: " << gold << std::endl;
    std::cout << "Experience: " << experience << "/" << (level * 100) << std::endl;
    std::cout << "=====================" << std::endl;
}


// TODO: Override calculateDamage to include weapon bonus
// HINTS:
// - If weapon is equipped, add weapon's damage bonus
// - Return total damage
//
int Player::calculateDamage() const {
    // TODO: Calculate damage with weapon bonus
    int dmg = Character::calculateDamage();
    if (equipped_weapon) dmg += static_cast<Weapon*>(equipped_weapon)->getDamageBonus();//static_cast
    return dmg;  // REPLACE THIS
}


// TODO: Implement addItem
// HINTS:
// - Add item to inventory vector using push_back()
// - Print pickup message with item name
//
void Player::addItem(Item* item) {
    if (!item) return;
    inventory.push_back(item); // vector implementation .push_back
    std::cout << "Picked up: " << item->getName() << std::endl;
    // TODO: Add item to inventory
}


// TODO: Implement removeItem
// HINTS:
// - Search inventory for item by name (case-insensitive comparison)
// - If found: delete the item, then erase from vector
// - If not found: print error message
// - Remember: inventory.erase(inventory.begin() + i) to remove at index i
//
void Player::removeItem(const std::string& item_name) {
    // TODO: Find and remove item from inventory
    std::string target = item_name;
    std::transform(target.begin(), target.end(), target.begin(), ::tolower);
    //transform takes input range [begin, end), and output start iterator, and a function transforms each element
    //it writes the transformed result into the output
    //chatgpt
    
    for (size_t i = 0; i < inventory.size(); i++) {
        std::string test = inventory[i]->getName();
        std::transform(test.begin(), test.end(), test.begin(), ::tolower);

        if (test == target) {
            delete inventory[i];
            inventory.erase(inventory.begin() + i);
            return;
        }
    }
    std::cout << "Item not found: " << item_name << std::endl;
}


// TODO: Implement displayInventory
// HINTS:
// - Print header: "----- Inventory -----"
// - If inventory is empty, print "Empty"
// - Otherwise, loop through and print each item's name and type
// - Format: "- ItemName (ItemType)"
// - Print footer: "--------------------"
//
void Player::displayInventory() const {
    // TODO: Display all items in inventory
    std::cout << "----- Inventory -----" << std::endl;
    if (inventory.empty()) {
        std::cout << "Empty" << std::endl;
        } else {
            for (size_t i = 0; i < inventory.size(); i++) {
                std::cout << "- " << inventory[i]->getName() << " ("
                << inventory[i]->getType() << ")" << std::endl;
            }
        }
        std::cout << "---------------------" << std::endl;
}


// TODO: Implement hasItem
// HINTS:
// - Search inventory for item by name (case-insensitive)
// - Return true if found, false otherwise
// - Use same case-insensitive comparison as removeItem
//
bool Player::hasItem(const std::string& item_name) const {
    // TODO: Check if item exists in inventory
    std::string target = item_name;
    std::transform(target.begin(), target.end(), target.begin(), ::tolower);

    for (size_t i = 0; i < inventory.size(); i++) {
        std::string test = inventory[i]->getName();
        std::transform(test.begin(), test.end(), test.begin(), ::tolower);
        if (test == target) return true;
    }
    return false;
}


// TODO: Implement getItem
// HINTS:
// - Search inventory for item by name (case-insensitive)
// - Return pointer to item if found
// - Return NULL if not found
//
Item* Player::getItem(const std::string& item_name) {
    // TODO: Find and return item pointer
    std::string target = item_name;
    std::transform(target.begin(), target.end(), target.begin(), ::tolower);


    for (size_t i = 0; i < inventory.size(); i++) {
        std::string test = inventory[i]->getName();
        std::transform(test.begin(), test.end(), test.begin(), ::tolower);
        if (test == target) return inventory[i];
    }
    return NULL;
}

// TODO: Implement equipWeapon
// HINTS:
// - Get item from inventory using getItem()
// - Check if item exists (not NULL)
// - Check if item type is "Weapon"
// - If current weapon equipped, print unequip message
// - Set equipped_weapon pointer to this item
// - Print equip message
//
void Player::equipWeapon(const std::string& weapon_name) {
    // TODO: Equip weapon from inventory
    Item* item = getItem(weapon_name);
    if (!item) {
        std::cout << "No such item: " << weapon_name << std::endl;
        return;
    }
    
    if (item->getType() != "Weapon") {
        std::cout << "You can't equip that!" << std::endl;
        return;
    }


    if (equipped_weapon) std::cout << "Unequipped: " << equipped_weapon->getName() << std::endl;
    
    equipped_weapon = static_cast<Weapon*>(item);
    std::cout << "Equipped weapon: " << item->getName() << std::endl;
}


// TODO: Implement equipArmor
// HINTS:
// - Similar to equipWeapon but for armor
// - Check if item type is "Armor"
// - Set equipped_armor pointer
//
void Player::equipArmor(const std::string& armor_name) {
    // TODO: Equip armor from inventory
    Item* item = getItem(armor_name);
    if (!item) {
        std::cout << "No such item: " << armor_name << std::endl;
        return;
    }
    if (item->getType() != "Armor") {
        std::cout << "You can't equip that!" << std::endl;
        return;
    }
    if (equipped_armor)std::cout << "Unequipped: " << equipped_armor->getName() << std::endl;
    equipped_armor = static_cast<Armor*>(item);
    std::cout << "Equipped armor: " << item->getName() << std::endl;
}


// TODO: Implement unequipWeapon
// HINTS:
// - Check if weapon is currently equipped
// - If so, print message and set equipped_weapon to NULL
// - If not, print error message
//
void Player::unequipWeapon() {
    // TODO: Unequip current weapon
    if (!equipped_weapon) {
        std::cout << "No weapon is equipped." << std::endl;
        return;
    }
    std::cout << "Unequipped weapon: " << equipped_weapon->getName() << std::endl;
    equipped_weapon = NULL;
}


// TODO: Implement unequipArmor
// HINTS:
// - Similar to unequipWeapon
// - Set equipped_armor to NULL
//
void Player::unequipArmor() {
    // TODO: Unequip current armor
    if (!equipped_armor) {
        std::cout << "No armor is equipped." << std::endl;
        return;
    }
    std::cout << "Unequipped armor: " << equipped_armor->getName() << std::endl;
    equipped_armor = NULL;
}


// TODO: Implement useItem
// HINTS:
// - Get item from inventory using getItem()
// - Check if item exists (not NULL)
// - Check if item type is "Consumable"
// - Cast to Consumable*: Consumable* consumable = static_cast<Consumable*>(item)
// - Check if already used: consumable->isUsed()
// - Get healing amount: consumable->getHealingAmount()
// - Call heal() with that amount
// - Call consumable->use() to mark as used
// - Remove item from inventory (it's been consumed!)
//
void Player::useItem(const std::string& item_name) {
    // TODO: Use consumable item
    Item* item = getItem(item_name);
    if (!item) {
        std::cout << "No such item: " << item_name << std::endl;
        return;
    }
    if (item->getType() != "Consumable") {
        std::cout << "You can't use that!" << std::endl;
        return;
    }

    Consumable* c = static_cast<Consumable*>(item);
    if (c->isUsed()) {
        std::cout << item->getName() << " is already used!" << std::endl;
        return;
    }

    heal(c->getHealingAmount());
    c->use();
    removeItem(item_name);
}


// TODO: Implement gainExperience
// HINTS:
// - Add experience points
// - Print message showing exp gained
// - Check if enough exp to level up: if (experience >= level * 100)
// - If so, call levelUp()
//
void Player::gainExperience(int exp) {
    // TODO: Add experience and check for level up
    experience += exp;
    std::cout << "Gained " << exp << " EXP!" << std::endl;
    if (experience >= level * 100)levelUp();
}


// TODO: Implement levelUp
// HINTS:
// - Increment level
// - Reset experience to 0
// - Increase stats:
//   * Increase max_hp by 10 (use setMaxHP())
//   * Set current_hp to max (full heal on level up)
//   * Increase attack by 2
//   * Increase defense by 1
// - Print celebratory level up message
// - Display new stats
//
void Player::levelUp() {
    // TODO: Level up the player
    level++;
    experience = 0;

    setMaxHP(getMaxHP() + 10);
    setCurrentHP(getMaxHP());

    setAttack(getAttack() + 2);
    setDefense(getDefense() + 1);

    std::cout << "===== LEVEL UP! =====" << std::endl;
    std::cout << "You are now level " << level << "!" << std::endl;
    displayStats();
}
///instantiating warrior, mage, and rogue with different hp, attack, defense stack
///from the super class Player
Warrior::Warrior(const std::string &name):Player(name){
    setMaxHP(130);
    setCurrentHP(130);
    setAttack(getAttack() + 5);
    setDefense(getDefense() + 3);
}
int Warrior::calculateDamage() const{
    return Player::calculateDamage()+3;
}
void Warrior::displayStats() const{
    std::cout << "[Warrior] ";
    Player::displayStats();
}

Mage::Mage(const std::string& name)
    : Player(name)
{
    setMaxHP(70);
    setCurrentHP(70);
    setAttack(getAttack() + 2);
    setDefense(getDefense() - 1);
}
//Mage does a random damage skill depending on 0, 1, 2
//each of his skill does different damage
int Mage::calculateDamage() const {
    int roll = rand() % 3;

    if (roll == 0) {
        std::cout << "You cast Fireball!\n";
        return getAttack() + 12;
    } else if (roll == 1) {
        std::cout << "You cast Ice Spike!\n";
        return getAttack() + 7;
    } else {
        std::cout << "You cast Magic Missile.\n";
        return getAttack() + 3;
    }
}
void Mage::displayStats() const {
    std::cout << "[Mage] ";
    Player::displayStats();
}

Rogue::Rogue(const std::string& name)
    : Player(name)
{
    setMaxHP(90);
    setCurrentHP(90);

    setAttack(getAttack() + 7);
    setDefense(getDefense() - 3);
}
//Rogue does a critical daamge 30% chance
//implement rand() to calculate the probability and cast it
int Rogue::calculateDamage() const {
    if (rand() % 10 < 3) {
        std::cout << "Critical Strike!\n";
        return getAttack() * 2 + 5;
    }
    return Player::calculateDamage() + 1;
}

void Rogue::displayStats() const {
    std::cout << "[Rogue] ";
    Player::displayStats();
}