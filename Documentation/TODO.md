# RPG Lab - Implementation Guide (TODO)

This document provides detailed step-by-step tasks for implementing the RPG game. Follow the weeks in order, completing each section before moving to the next.

---

## Week 1: Foundation - Basic Classes (After Lectures 1-2)

**Time Estimate**: 6-8 hours  
**Concepts Needed**: Classes, constructors/destructors, encapsulation, new/delete, std::vector, std::string

### Task 1.1: Implement Character Base Class (2 hours)

**File**: `Character.h` and `Character.cpp`

**What to do**:
1. Review the provided class declaration in Character.h
2. Implement the constructor:
   - Initialize all member variables using initializer list
   - Set current_hp equal to max_hp
   - Set alive to true
3. Implement the destructor:
   - Add a debug print statement (optional but helpful)
   - No dynamic memory to clean up in base Character
4. Implement `calculateDamage()`:
   - Return attack value plus random bonus (0-4)
   - Use: `attack + (rand() % 5)`
5. Implement `takeDamage(int damage)`:
   - Calculate actual damage: damage - defense (minimum 0)
   - Subtract from current_hp
   - If hp <= 0, set to 0 and alive to false
   - Print damage message with current HP
6. Implement `heal(int amount)`:
   - Add amount to current_hp
   - Cap at max_hp (don't exceed maximum)
   - Print healing message
7. Implement `displayStats()`:
   - Print name and HP in format: "Name [HP: current/max]"
8. Implement `displayStatus()`:
   - Brief one-line status (used in combat)

**Testing**:
```cpp
// Create a test program:
int main() {
    Character hero("Hero", 100, 10, 5);
    hero.displayStats();
    hero.takeDamage(20);
    hero.heal(10);
    return 0;
}
```

**Success Criteria**:
- Program compiles without errors
- Character takes damage correctly
- HP doesn't go below 0 or above max
- Character dies when HP reaches 0

---

### Task 1.2: Implement Item Base Class (1 hour)

**Files**: `Item.h` and `Item.cpp`

**What to do**:
1. Implement Item constructor:
   - Initialize all member variables
   - Use initializer list
2. Implement destructor:
   - Add debug print (optional)
3. Implement `displayInfo()`:
   - Print item name, description, and value
   - Format: "[ITEM] Name\n  Description\n  Value: X"
4. Implement `displayBrief()`:
   - One line: "Name (Type)"

**Testing**:
```cpp
int main() {
    Item sword("Iron Sword", "A sturdy blade", "Weapon", 5);
    sword.displayInfo();
    return 0;
}
```

---

### Task 1.3: Implement Weapon Class (1 hour)

**Files**: `Item.h` and `Item.cpp`

**What to do**:
1. Implement Weapon constructor:
   - Call base Item constructor with initializer list
   - Initialize damage_bonus
   - Type should be "Weapon"
2. Override `displayInfo()`:
   - Show weapon-specific format
   - Include damage bonus information
   - Format: "[WEAPON] Name\n  Description\n  Damage Bonus: +X"

**Testing**:
```cpp
int main() {
    Weapon sword("Iron Sword", "A sturdy blade", 5);
    sword.displayInfo();
    Item* item_ptr = &sword;
    item_ptr->displayInfo();  // Should call Weapon version
    return 0;
}
```

---

### Task 1.4: Implement Armor Class (1 hour)

**Files**: `Item.h` and `Item.cpp`

**What to do**:
1. Implement Armor constructor:
   - Call base Item constructor
   - Initialize defense_bonus
   - Type should be "Armor"
2. Override `displayInfo()`:
   - Show armor-specific format
   - Include defense bonus
   - Format: "[ARMOR] Name\n  Description\n  Defense Bonus: +X"

**Testing**:
```cpp
int main() {
    Armor chainmail("Chain Mail", "Protective armor", 3);
    chainmail.displayInfo();
    return 0;
}
```

---

### Task 1.5: Implement Consumable Class (1 hour)

**Files**: `Item.h` and `Item.cpp`

**What to do**:
1. Implement Consumable constructor:
   - Call base Item constructor
   - Initialize healing_amount
   - Initialize used to false
   - Type should be "Consumable"
2. Override `displayInfo()`:
   - Show consumable-specific format
   - Include healing amount
   - Format: "[CONSUMABLE] Name\n  Description\n  Restores: X HP"
3. Implement `use()`:
   - Check if already used
   - If not used: print message and set used to true
   - If already used: print error message

**Testing**:
```cpp
int main() {
    Consumable potion("Health Potion", "Restores health", 30);
    potion.displayInfo();
    potion.use();  // Should work
    potion.use();  // Should print "already used"
    return 0;
}
```

---

### Task 1.6: Basic Inventory System (2 hours)

**Goal**: Create a simple test program that manages a vector of items

**What to do**:
1. Create a test program (`test_inventory.cpp`)
2. Create a `std::vector<Item*>` to hold items
3. Add several items (weapons, armor, consumables)
4. Display all items
5. Remove an item by name (search and erase)
6. **IMPORTANT**: Delete all items before program ends

**Example**:
```cpp
#include <vector>
#include "Item.h"

int main() {
    std::vector<Item*> inventory;
    
    // Add items
    inventory.push_back(new Weapon("Sword", "Sharp blade", 5));
    inventory.push_back(new Armor("Shield", "Wooden shield", 2));
    inventory.push_back(new Consumable("Potion", "Heals", 20));
    
    // Display all
    for (int i = 0; i < inventory.size(); i++) {
        inventory[i]->displayInfo();
    }
    
    // Clean up - VERY IMPORTANT!
    for (int i = 0; i < inventory.size(); i++) {
        delete inventory[i];
    }
    inventory.clear();
    
    return 0;
}
```

**Testing**:
- Compile and run
- Add valgrind check: `valgrind --leak-check=full ./test_inventory`
- Should show "no leaks are possible"

---

### Week 1 Checkpoint

Before moving to Week 2, verify:
- ✓ Character class fully functional
- ✓ All Item classes work correctly
- ✓ Can create and manage vectors of items
- ✓ No memory leaks in test programs
- ✓ Understand constructors and destructors
- ✓ Comfortable with new/delete

**If any checklist item is incomplete, review lecture materials and fix before proceeding.**

---

## Week 2: Inheritance and Polymorphism (After Lectures 3-4)

**Time Estimate**: 8-10 hours  
**Concepts Needed**: Inheritance, virtual functions, constructor chaining, polymorphism

### Task 2.1: Implement Player Class - Basic Structure (2 hours)

**Files**: `Player.h` and `Player.cpp`

**What to do**:
1. Implement Player constructor:
   - Call Character base constructor with appropriate values
     - Starting HP: 100
     - Starting attack: 10
     - Starting defense: 5
   - Initialize level to 1
   - Initialize experience and gold to 0
   - Initialize equipped pointers to NULL
   - Inventory vector starts empty automatically
2. Implement Player destructor:
   - **CRITICAL**: Delete all items in inventory
   - Loop through inventory vector and delete each Item*
   - Clear the vector
   - DON'T delete equipped_weapon/armor (they point to items already in inventory)
3. Override `displayStats()`:
   - Show player-specific information
   - Include level, HP, attack, defense, gold, experience
   - Show equipped weapon and armor bonuses
   - Format nicely with headers and separators

**Testing**:
```cpp
int main() {
    Player hero("Alice");
    hero.displayStats();
    hero.takeDamage(20);  // Inherited method
    hero.displayStats();
    return 0;
}
```

---

### Task 2.2: Implement Player Inventory Management (2 hours)

**Files**: `Player.cpp`

**What to do**:
1. Implement `addItem(Item* item)`:
   - Check if item is NULL
   - Add to inventory vector
   - Print pickup message
2. Implement `removeItem(const std::string& item_name)`:
   - Search inventory for item (case-insensitive)
   - Use std::transform to convert to lowercase for comparison
   - If found: delete the item and erase from vector
   - If not found: print error message
3. Implement `displayInventory()`:
   - Print header
   - If empty, print "Empty"
   - Otherwise, list all items with names and types
4. Implement `hasItem(const std::string& item_name)`:
   - Search inventory (case-insensitive)
   - Return true if found, false otherwise
5. Implement `getItem(const std::string& item_name)`:
   - Search inventory (case-insensitive)
   - Return pointer if found, NULL otherwise

**Helper for case-insensitive comparison**:
```cpp
std::string lower = item_name;
std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
```

**Testing**:
```cpp
int main() {
    Player hero("Bob");
    hero.addItem(new Weapon("Sword", "Sharp", 5));
    hero.addItem(new Consumable("Potion", "Heals", 20));
    hero.displayInventory();
    hero.removeItem("potion");  // Case insensitive
    hero.displayInventory();
    return 0;
}
```

---

### Task 2.3: Implement Player Equipment System (2 hours)

**Files**: `Player.cpp`

**What to do**:
1. Implement `equipWeapon(const std::string& weapon_name)`:
   - Get item from inventory by name
   - Check if it exists (NULL check)
   - Check if type is "Weapon"
   - If currently have weapon equipped, print unequip message
   - Set equipped_weapon pointer to this item
   - Print equip message
2. Implement `equipArmor(const std::string& armor_name)`:
   - Similar to equipWeapon but for armor
   - Check type is "Armor"
   - Set equipped_armor pointer
3. Implement `unequipWeapon()`:
   - Check if weapon is equipped
   - If so, set to NULL and print message
4. Implement `unequipArmor()`:
   - Similar to unequipWeapon
5. Override `calculateDamage()`:
   - Call base Character::calculateDamage()
   - If weapon equipped, add weapon's damage bonus
   - Return total damage
6. Implement `useItem(const std::string& item_name)`:
   - Get item from inventory
   - Check if it's a Consumable
   - Check if already used
   - Cast to Consumable* and get healing amount
   - Call heal() with that amount
   - Call consumable->use() to mark as used
   - Remove item from inventory

**Testing**:
```cpp
int main() {
    Player hero("Charlie");
    hero.addItem(new Weapon("Sword", "Sharp", 5));
    hero.addItem(new Armor("Chainmail", "Strong", 3));
    
    hero.equipWeapon("sword");
    hero.equipArmor("chainmail");
    
    hero.displayStats();
    
    int dmg = hero.calculateDamage();
    std::cout << "Damage: " << dmg << std::endl;  // Should include weapon bonus
    
    return 0;
}
```

---

### Task 2.4: Implement Player Leveling System (1 hour)

**Files**: `Player.cpp`

**What to do**:
1. Implement `gainExperience(int exp)`:
   - Add experience
   - Print message
   - Check if enough exp to level up (level * 100)
   - If so, call levelUp()
2. Implement `levelUp()`:
   - Increment level
   - Reset experience to 0
   - Increase max_hp by 10
   - Set current_hp to max (full heal on level up)
   - Increase attack by 2
   - Increase defense by 1
   - Print celebratory message
   - Display new stats

**Testing**:
```cpp
int main() {
    Player hero("Dana");
    hero.displayStats();
    hero.gainExperience(100);  // Should trigger level up
    hero.displayStats();
    return 0;
}
```

---

### Task 2.5: Implement Monster Base Class (1 hour)

**Files**: `Monster.h` and `Monster.cpp`

**What to do**:
1. Implement Monster constructor:
   - Call Character base constructor
   - Initialize experience_reward and gold_reward
   - Loot table starts empty
2. Implement Monster destructor:
   - **CRITICAL**: Delete all items in loot_table
   - Loop and delete each Item*
   - Clear vector
3. Override `displayStats()`:
   - Show monster name and HP
   - Format: "MonsterName [HP: current/max]"
4. Implement `addLoot(Item* item)`:
   - Check if item is NULL
   - Add to loot_table vector
5. Implement `dropLoot()`:
   - Create copy of loot_table
   - Clear original loot_table (transfer ownership!)
   - Return the copy
6. Implement `getAttackMessage()`:
   - Return default message: "MonsterName attacks!"

**Testing**:
```cpp
int main() {
    Monster orc("Orc", 50, 8, 3, 20, 10);
    orc.addLoot(new Consumable("Potion", "Heals", 15));
    orc.displayStats();
    orc.takeDamage(30);
    
    std::vector<Item*> loot = orc.dropLoot();
    // Clean up loot
    for (int i = 0; i < loot.size(); i++) {
        delete loot[i];
    }
    
    return 0;
}
```

---

### Task 2.6: Implement Specific Monster Types (2 hours)

**Files**: `Monster.cpp`

**What to do**:

#### Goblin Class:
1. Implement constructor:
   - Call Monster constructor with:
     - Name: "Goblin"
     - HP: 30, Attack: 5, Defense: 2
     - Experience: 10, Gold: 5
   - Add small potion to loot table
2. Override `getAttackMessage()`:
   - Return: "The goblin swipes at you with its rusty dagger!"

#### Skeleton Class:
1. Implement constructor:
   - Call Monster constructor with:
     - Name: "Skeleton"
     - HP: 40, Attack: 8, Defense: 4
     - Experience: 20, Gold: 10
   - Add old sword to loot table
2. Override `getAttackMessage()`:
   - Return: "The skeleton rattles its bones and slashes with a sword!"

#### Dragon Class (BOSS):
1. Implement constructor:
   - Call Monster constructor with:
     - Name: "Dragon"
     - HP: 150, Attack: 20, Defense: 10
     - Experience: 100, Gold: 50
   - Add legendary weapon, dragon scale armor, and greater potion to loot
2. Override `getAttackMessage()`:
   - Return: "The dragon breathes fire at you!"
3. Override `calculateDamage()`:
   - Call Monster::calculateDamage() to get base damage
   - Add bonus fire damage: base + 5
   - Return total

**Testing - Polymorphism!**:
```cpp
int main() {
    // Test polymorphism - base class pointers to derived objects
    Monster* monsters[3];
    monsters[0] = new Goblin();
    monsters[1] = new Skeleton();
    monsters[2] = new Dragon();
    
    for (int i = 0; i < 3; i++) {
        monsters[i]->displayStats();
        std::cout << monsters[i]->getAttackMessage() << std::endl;
        int dmg = monsters[i]->calculateDamage();
        std::cout << "Damage: " << dmg << std::endl;
        std::cout << std::endl;
    }
    
    // Clean up
    for (int i = 0; i < 3; i++) {
        delete monsters[i];
    }
    
    return 0;
}
```

**Success Criteria**:
- Each monster shows correct stats
- Attack messages are monster-specific
- Dragon deals extra damage
- All virtual functions work correctly through base pointers

---

### Week 2 Checkpoint

Before moving to Week 3, verify:
- ✓ Player class fully functional with inventory
- ✓ Equipment system works
- ✓ Leveling system works
- ✓ All monster types implemented
- ✓ Virtual functions work correctly (test with base class pointers)
- ✓ No memory leaks (valgrind clean)
- ✓ Understand constructor chaining
- ✓ Understand polymorphism

---

## Week 3: Integration - Complete Game (After Lecture 5)

**Time Estimate**: 10-12 hours  
**Concepts Needed**: std::map, composition, object ownership, complete system integration

### Task 3.1: Implement Room Class - Basic Structure (2 hours)

**Files**: `Room.h` and `Room.cpp`

**What to do**:
1. Implement Room constructor:
   - Initialize name and description
   - Set visited to false
   - Set monster to NULL
   - Vectors start empty automatically
2. Implement Room destructor:
   - **CRITICAL**: Delete monster if present
   - **CRITICAL**: Delete all items in items vector
   - DON'T delete rooms in exits map (Game owns those)
3. Implement `display()`:
   - Print formatted room information:
     - Room name (with decorative borders)
     - Description
     - Monster warning if present
     - List of items if any
     - Available exits
4. Implement `displayExits()`:
   - Print "Exits: "
   - Iterate through exits map
   - Print all directions (north, south, east, west)
   - Comma-separated list

**Testing**:
```cpp
int main() {
    Room entrance("Entrance", "A dark corridor");
    entrance.display();
    return 0;
}
```

---

### Task 3.2: Implement Room Connections (1 hour)

**Files**: `Room.cpp`

**What to do**:
1. Implement `addExit(const std::string& direction, Room* room)`:
   - Check if room is not NULL
   - Add to exits map: `exits[direction] = room`
2. Implement `getExit(const std::string& direction)`:
   - Look up direction in exits map
   - Use iterator: `exits.find(direction)`
   - If found, return the Room*
   - If not found, return NULL
3. Implement `hasExit(const std::string& direction)`:
   - Use exits.find() or exits.count()
   - Return true if exists, false otherwise

**Testing**:
```cpp
int main() {
    Room room1("Room 1", "First room");
    Room room2("Room 2", "Second room");
    
    room1.addExit("north", &room2);
    room2.addExit("south", &room1);
    
    room1.display();
    
    Room* next = room1.getExit("north");
    if (next) {
        next->display();
    }
    
    return 0;
}
```

---

### Task 3.3: Implement Room Content Management (1 hour)

**Files**: `Room.cpp`

**What to do**:
1. Implement `setMonster(Monster* m)`:
   - Simply: `monster = m`
2. Implement `getMonster()`:
   - Return monster pointer
3. Implement `hasMonster()`:
   - Return true if monster exists AND is alive
4. Implement `clearMonster()`:
   - If monster exists, delete it
   - Set monster to NULL
5. Implement `addItem(Item* item)`:
   - Check if not NULL
   - Add to items vector
6. Implement `removeItem(const std::string& item_name)`:
   - Search items vector (case-insensitive)
   - If found, erase from vector
   - **DON'T delete** (ownership transferred to player)
7. Implement `displayItems()`:
   - Print each item's name in a list
8. Implement `getItem(const std::string& item_name)`:
   - Search items vector (case-insensitive)
   - Return pointer if found, NULL otherwise

**Testing**:
```cpp
int main() {
    Room room("Armory", "Weapons everywhere");
    room.addItem(new Weapon("Sword", "Sharp", 5));
    room.setMonster(new Goblin());
    
    room.display();
    
    if (room.hasMonster()) {
        std::cout << "Monster present!" << std::endl;
    }
    
    return 0;
}
```

---

### Task 3.4: Implement Game Class - World Creation (2 hours)

**Files**: `Game.h` and `Game.cpp`

**What to do**:
1. Implement Game constructor:
   - Initialize player to NULL
   - Initialize current_room to NULL
   - Set game_over and victory to false
   - World map starts empty
2. Implement Game destructor:
   - Delete player if exists
   - **Iterate through world map** and delete each Room*
   - Use iterator: `for (std::map<std::string, Room*>::iterator it = world.begin(); ...)`
   - Clear the map
3. Implement `addRoom(Room* room)`:
   - Check if not NULL
   - Add to world map using room's name as key
4. Implement `connectRooms(...)`:
   - Look up both rooms in world map
   - If both exist:
     - Add forward direction
     - Determine reverse direction (north↔south, east↔west)
     - Add reverse direction
5. Implement `initializeWorld()`:
   - Create all rooms (entrance, hallway, armory, treasury, throne room)
   - Add rooms to world
   - Connect rooms
   - Add monsters to appropriate rooms
   - Add items to rooms
   - Set current_room to entrance
6. Implement `createStartingInventory()`:
   - Give player basic weapon (rusty dagger)
   - Give player basic consumable (bread)

**Testing**:
```cpp
int main() {
    Game game;
    // Can't test much yet, but should compile
    return 0;
}
```

---

### Task 3.5: Implement Game Loop and Commands (3 hours)

**Files**: `Game.cpp`

**What to do**:
1. Implement `run()`:
   - Print welcome message
   - Get player name from input
   - Create player
   - Call initializeWorld()
   - Call createStartingInventory()
   - Display starting room
   - **Main loop**: while (!game_over)
     - Print prompt
     - Get command
     - Convert to lowercase
     - Call processCommand()
     - Check victory/defeat conditions
2. Implement `processCommand(const std::string& command)`:
   - Parse command into verb and object
   - Use std::istringstream
   - Dispatch to appropriate method:
     - "go" → move()
     - "look" → look()
     - "attack" → attack()
     - "pickup" → pickupItem()
     - "inventory" → inventory()
     - "use" → useItem()
     - "equip" → equip()
     - "stats" → player->displayStats()
     - "help" → help()
     - "quit" → set game_over to true
3. Implement `move(const std::string& direction)`:
   - Check if monster blocks path
   - Get exit in specified direction
   - If exists:
     - Update current_room
     - Display new room
     - Mark as visited
   - Otherwise print error
4. Implement `look()`:
   - Display current room
5. Implement `attack()`:
   - Check if monster in room
   - If yes, call combat()
   - If no, print message
6. Implement `pickupItem(const std::string& item_name)`:
   - Get item from room
   - If exists:
     - Add to player inventory
     - Remove from room
   - Otherwise print error
7. Implement `inventory()`:
   - Call player->displayInventory()
8. Implement `useItem(const std::string& item_name)`:
   - Call player->useItem()
9. Implement `equip(const std::string& item_name)`:
   - Get item from player inventory
   - Check if it's Weapon or Armor
   - Call appropriate equip method
10. Implement `help()`:
    - Display all available commands

**Testing**: Now you can run the game and test individual commands!

---

### Task 3.6: Implement Combat System (2 hours)

**Files**: `Game.cpp`

**What to do**:
1. Implement `combat(Monster* monster)`:
   - Print "COMBAT BEGINS"
   - **Combat loop**: while both alive
     - Display both status
     - Prompt for player action (attack/use/flee)
     - **If attack**:
       - Calculate player damage
       - Monster takes damage
       - If monster dies:
         - Print victory message
         - Give player experience and gold
         - Get loot from monster
         - Add loot to room
         - Check if was Dragon (victory!)
         - Clear monster from room
         - Break from loop
     - **If use**:
       - Extract item name from command
       - Call player->useItem()
     - **If flee**:
       - Print message
       - Break from loop
     - **Monster turn** (if still alive):
       - Print attack message
       - Calculate monster damage
       - Player takes damage
   - Print "COMBAT ENDS"

**Testing**: Now you can fight monsters!

---

### Task 3.7: Implement main.cpp (30 minutes)

**Files**: `main.cpp`

**What to do**:
1. Include necessary headers
2. Seed random number generator
3. Create Game object
4. Call game.run()
5. Add exception handling (try-catch)

**Code**:
```cpp
#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Seed random number generator for combat
    srand(static_cast<unsigned int>(time(0)));
    
    try {
        Game game;
        game.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
```

---

### Task 3.8: Final Testing and Debugging (2 hours)

**What to do**:
1. **Compile without errors**:
   ```bash
   make clean
   make
   ```
2. **Run the game**:
   ```bash
   ./bin/dungeon_rpg
   ```
3. **Test all features**:
   - Movement between rooms
   - Picking up items
   - Inventory management
   - Equipping weapons and armor
   - Using consumables
   - Combat system
   - Leveling up
   - Different monster types
   - Victory condition (defeating dragon)
4. **Check for memory leaks**:
   ```bash
   valgrind --leak-check=full ./bin/dungeon_rpg
   ```
   Play through and quit normally - should show no leaks
5. **Fix any bugs found**

**Common bugs to check**:
- Segfaults (NULL pointer dereferences)
- Memory leaks (valgrind)
- Infinite loops
- Commands not working
- Combat not ending properly
- Items not being picked up/used correctly

---

### Week 3 Checkpoint

Final verification:
- ✓ Complete game compiles
- ✓ Can navigate between rooms
- ✓ Can fight and defeat monsters
- ✓ Can manage inventory
- ✓ Can level up
- ✓ Can win game by defeating dragon
- ✓ No memory leaks (valgrind clean)
- ✓ No segmentation faults
- ✓ All commands work properly

---

## Optional Extensions

If you finish early or want extra credit, consider:

### Extension 1: Save/Load System
- Serialize game state to file
- Load game state from file
- Save player stats, inventory, room states

### Extension 2: More Monster Types
- Troll (high HP, low damage)
- Ghost (high evasion)
- Wizard (ranged attacks)

### Extension 3: More Item Types
- Keys (unlock doors)
- Scrolls (one-time spell effects)
- Gold items (just for selling)

### Extension 4: Character Classes
- Warrior (high HP, bonus attack)
- Mage (low HP, magic attacks)
- Rogue (high damage, low defense)

### Extension 5: Shop System
- NPC shopkeeper
- Buy/sell items
- Gold economy

---

## Debugging Tips

### Common Errors and Solutions

**Compilation Error: "undefined reference to vtable"**
- **Cause**: Declared virtual function but didn't implement it
- **Solution**: Implement all virtual functions

**Runtime Error: Segmentation fault**
- **Cause**: Dereferencing NULL pointer
- **Solution**: Add NULL checks before using pointers
- **Debug**: Run with gdb: `gdb ./bin/dungeon_rpg`, then `run`, then `bt` for backtrace

**Runtime Error: Memory leak**
- **Cause**: Not deleting dynamically allocated objects
- **Solution**: Check all destructors delete owned objects
- **Debug**: Run with valgrind: `valgrind --leak-check=full ./bin/dungeon_rpg`

**Logic Error: Virtual function not called**
- **Cause**: Not using pointer or reference to base class
- **Solution**: Use base class pointer/reference for polymorphism

**Compilation Error: "no matching constructor"**
- **Cause**: Didn't call base class constructor
- **Solution**: Use initializer list: `Derived() : Base(args) { }`

---

## Getting Unstuck

If you're stuck on a task:

1. **Review lecture materials** for that week
2. **Read the relevant section** in this TODO
3. **Check the provided skeleton code** for hints
4. **Draw diagrams** of what you're trying to implement
5. **Test in isolation** - create small test program
6. **Use print statements** to debug
7. **Check for NULL pointers** before dereferencing
8. **Ask for help** - office hours, Ed discussion, study group

---

## Time Management

Suggested schedule (total ~30 hours):

- **Week 1** (8 hours):
  - Day 1-2: Character and Item classes (4 hours)
  - Day 3-4: Item hierarchy and testing (4 hours)

- **Week 2** (10 hours):
  - Day 1-2: Player class (4 hours)
  - Day 3-4: Monster hierarchy (4 hours)
  - Day 5: Testing and debugging (2 hours)

- **Week 3** (12 hours):
  - Day 1-2: Room class (3 hours)
  - Day 3-4: Game class world creation (3 hours)
  - Day 5-6: Commands and combat (4 hours)
  - Day 7: Final testing and debugging (2 hours)

**Start early! Don't wait until the last minute!**

---

## Submission Checklist

Before submitting, verify:

□ All files compile without errors  
□ Game runs and is playable start to finish  
□ Can defeat dragon and win  
□ No memory leaks (valgrind clean)  
□ No segmentation faults  
□ All commands work  
□ Code is well-commented  
□ README is updated  
□ Makefile works  
□ Submitted all required files  

**Good luck!**
