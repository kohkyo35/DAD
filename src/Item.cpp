#include "Item.h"

// ============================================================================
// Base Item class implementation
// ============================================================================

// TODO: Implement Item constructor
// HINTS:
// - Use initializer list to initialize all member variables
// - Parameters map directly to member variables
//
Item::Item(const std::string& name, const std::string& description,
           const std::string& type, int value)
    : name(name), description(description), type(type), value(value) {
}


// TODO: Implement Item destructor
// HINTS:
// - Can add debug output if helpful
//
Item::~Item() {
}


// TODO: Implement displayInfo (base version)
// HINTS:
// - Print item name, description, and value
// - Format: 
//   [ITEM] ItemName
//     Description text
//     Value: X
//
void Item::displayInfo() const {
    // TODO: Display item information
}


// TODO: Implement displayBrief
// HINTS:
// - One line format: "Name (Type)"
// - Example: "Iron Sword (Weapon)"
//
void Item::displayBrief() const {
    // TODO: Display brief item info
}


// ============================================================================
// Weapon class implementation
// ============================================================================

// TODO: Implement Weapon constructor
// HINTS:
// - MUST call base Item constructor using initializer list
// - Type should be "Weapon"
// - Value is the damage bonus
// - Also initialize damage_bonus member
// - Format: Weapon::Weapon(...) : Item(name, desc, "Weapon", damage), damage_bonus(damage) { }
//
Weapon::Weapon(const std::string& name, const std::string& description, int damage)
    : Item(name, description, "Weapon", damage), damage_bonus(damage) {
}


// TODO: Override displayInfo for Weapon
// HINTS:
// - Print weapon-specific format
// - Use getName(), getDescription(), getDamageBonus()
// - Format:
//   [WEAPON] WeaponName
//     Description
//     Damage Bonus: +X
//
void Weapon::displayInfo() const {
    // TODO: Display weapon-specific information
}


// ============================================================================
// Armor class implementation
// ============================================================================

// TODO: Implement Armor constructor
// HINTS:
// - MUST call base Item constructor using initializer list
// - Type should be "Armor"
// - Value is the defense bonus
// - Also initialize defense_bonus member
//
Armor::Armor(const std::string& name, const std::string& description, int defense)
    : Item(name, description, "Armor", defense), defense_bonus(defense) {
}


// TODO: Override displayInfo for Armor
// HINTS:
// - Print armor-specific format
// - Format:
//   [ARMOR] ArmorName
//     Description
//     Defense Bonus: +X
//
void Armor::displayInfo() const {
    // TODO: Display armor-specific information
}


// ============================================================================
// Consumable class implementation
// ============================================================================

// TODO: Implement Consumable constructor
// HINTS:
// - MUST call base Item constructor using initializer list
// - Type should be "Consumable"
// - Value is the healing amount
// - Initialize healing_amount and set used to false
//
Consumable::Consumable(const std::string& name, const std::string& description, 
                       int healing)
    : Item(name, description, "Consumable", healing), 
      healing_amount(healing), used(false) {
}


// TODO: Override displayInfo for Consumable
// HINTS:
// - Print consumable-specific format
// - Format:
//   [CONSUMABLE] ConsumableName
//     Description
//     Restores: X HP
//
void Consumable::displayInfo() const {
    // TODO: Display consumable-specific information
}


// TODO: Implement use() function
// HINTS:
// - Check if already used
// - If not used: print message and set used to true
// - If already used: print error message
// - Format: "Used ItemName! Restored X HP."
//
void Consumable::use() {
    // TODO: Implement use logic
}
