#include "Game.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// TODO: Implement Game constructor
Game::Game() : player(NULL), current_room(NULL),
               game_over(false), victory(false){
}


// TODO: Implement Game destructor
Game::~Game()
{
    // TODO: Clean up player and all rooms
    if (player != NULL)
    {
        delete player;
        player = NULL;
    }

    for (auto &pair : world)
    {
        delete pair.second;
    }
    world.clear();
}
// TODO: Implement initializeWorld
// HINTS:
// - Create all rooms with new
// - Add each room to world using addRoom()
// - Connect rooms using connectRooms()
// - Add monsters to appropriate rooms using room->setMonster()
// - Add items to rooms using room->addItem()
// - Set current_room to starting room (entrance)
//
// SUGGESTED WORLD LAYOUT:
//                [Throne Room]
//                     |
//     [Armory] - [Hallway] - [Treasury]
//                     |
//                 [Entrance]
//
// MONSTERS:
// - Hallway: Goblin
// - Armory: Skeleton
// - Treasury: Skeleton
// - Throne Room: Dragon (boss!)
//
// ITEMS:
// - Entrance: Small Potion
// - Armory: Iron Sword, Chain Mail
// - Treasury: Health Potion
//
void Game::initializeWorld()
{
    // TODO: Create rooms
    // Room* entrance = new Room("Dungeon Entrance", "A dark stone corridor...");
    Room *entrance = new Room("Entrance", "You stand at the entrance of a dark stone dungeon.");
    Room *hallway = new Room("Hallway", "A long, dim corridor connects several rooms of the dungeon.");
    Room *armory = new Room("Armory", "Racks of weapons and armor line the dusty walls.");
    Room *treasury = new Room("Treasury", "Glittering coins and chests fill the room.");
    Room *throne = new Room("Throne Room", "A vast chamber dominated by a looming throne. The air feels heavy.");
    // TODO: Add rooms to world
    addRoom(entrance);
    addRoom(hallway);
    addRoom(armory);
    addRoom(treasury);
    addRoom(throne);
    // TODO: Connect rooms bidirectionally
    connectRooms("Entrance", "north", "Hallway");
    connectRooms("Hallway", "west", "Armory");
    connectRooms("Hallway", "east", "Treasury");
    connectRooms("Hallway", "north", "Throne Room");
    // TODO: Add monsters
    Monster *goblin = new Monster("Goblin", 25, 5, 1);
    Monster *skeleton1 = new Monster("Skeleton", 30, 6, 2);
    Monster *skeleton2 = new Monster("Skeleton", 30, 6, 2);
    Monster *dragon = new Monster("Dragon", 80, 10, 4);

    world["Hallway"]->setMonster(goblin);
    world["Armory"]->setMonster(skeleton1);
    world["Treasury"]->setMonster(skeleton2);
    world["Throne Room"]->setMonster(dragon);
    // TODO: Add items
    world["Entrance"]->addItem(
        new Consumable("Small Potion", "A small potion that restores a bit of health.", 10));
    world["Armory"]->addItem(
        new Weapon("Iron Sword", "A solid iron sword. Better than a dagger.", 4));
    world["Armory"]->addItem(
        new Armor("Chain Mail", "Sturdy chain mail armor.", 3));
    world["Treasury"]->addItem(
        new Consumable("Health Potion", "A potion that restores a good amount of health.", 20));

    // TODO: Set starting room
    current_room = entrance;
}


// TODO: Implement createStartingInventory
// HINTS:
// - Give player starting weapon: Rusty Dagger (damage +2)
// - Give player starting food: Bread (heals 5 HP)
// - Use: player->addItem(new Weapon(...))
//
void Game::createStartingInventory()
{
    // TODO: Give player starting items
    player->addItem(
        new Weapon("Rusty Dagger", "An old, dull dagger, but still usuable.", 2));
    player->addItem(
        new Consumable("Bread", "A small loaf of bread.", 5));
}


// TODO: Implement addRoom
// HINTS:
// - Check if room pointer is not NULL
// - Add to world map using room's name as key
// - Use: world[room->getName()] = room
//
void Game::addRoom(Room *room)
{
    // TODO: Add room to world map
    if (room == NULL)
        return;
    world[room->getName()] = room;
}

// TODO: Implement connectRooms
// HINTS:
// - Look up both rooms in world map
// - If both exist:
//   - Add forward direction: room1->addExit(direction, room2)
//   - Determine reverse direction:
//     * north ↔ south
//     * east ↔ west
//   - Add reverse direction: room2->addExit(reverse, room1)
//
void Game::connectRooms(const std::string &room1_name, const std::string &direction,
                        const std::string &room2_name)
{
    // TODO: Connect rooms bidirectionally
    auto it1 = world.find(room1_name);
    auto it2 = world.find(room2_name);
    if (it1 == world.end() || it2 == world.end())
        return;

    Room *r1 = it1->second;
    Room *r2 = it2->second;

    // Forward direction
    r1->addExit(direction, r2);
    std::string rev;
    if (direction == "north")
        rev = "south";
    else if (direction == "south")
        rev = "north";
    else if (direction == "east")
        rev = "west";
    else if (direction == "west")
        rev = "east";

    if (!rev.empty())
    {
        r2->addExit(rev, r1);
    }
}

// TODO: Implement run - main game loop
// HINTS:
// - Call createStartingInventory()
// - Display starting room
// - Mark starting room as visited
// - Main loop:
//   - Check victory condition
//   - Check defeat condition (player dead)
//
void Game::run()
{
    // TODO: Implement main game loop
    // - Print welcome message and game title
    std::cout << "====================================\n";
    std::cout << "       DUNGEON ADVENTURE GAME       \n";
    std::cout << "====================================\n\n";

    // Get player name
    std::string name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    // - Get player name from input

    if (name.empty())
    {
        name = "Hero";
    }
    // - Create player: player
    player = new Player(name);

    // - Call initializeWorld()
    initializeWorld();
    createStartingInventory();

    look();
    //   - Print prompt: "> "
    while (!game_over)
    {
        if (!player->isAlive())
        {
            std::cout << "\nYou have fallen in the dungeon...\n";
            game_over = true;
            break;
        }
        if (victory)
        {
            std::cout << "\nYou have cleared the dungeon! Victory!\n";
            game_over = true;
            break;
        }
        //   - Get command (use std::getline)
        std::cout << "\n> ";

        std::string line;
        if (!std::getline(std::cin, line))
        {
            break;
        }
        if (line.empty())
            continue;
        //   - Convert to lowercase (use std::transform)
        // lowercase
        std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c)
                       { return std::tolower(c); });
        processCommand(line); //   - Call processCommand()
    }
    std::cout << "\nGame over.\n";
}

// TODO: Implement processCommand
// HINTS:
// - Parse command into verb and object
// - Extract first word as verb
// - Rest of line is object
// - Dispatch to appropriate method based on verb:
//   * "go" or "move" → move(object)
//   * "look" or "l" → look()
//   * "attack" or "fight" → attack()
//   * "pickup" or "get" or "take" → pickupItem(object)
//   * "inventory" or "i" → inventory()
//   * "use" → useItem(object)
//   * "equip" or "e" → equip(object)
//   * "stats" → player->displayStats()
//   * "help" or "h" or "?" → help()
//   * "quit" or "exit" → set game_over to true
//
void Game::processCommand(const std::string &command)
{
    // TODO: Parse and dispatch command
    std::istringstream iss(command);
    std::string verb;
    iss >> verb;

    std::string object;
    std::getline(iss, object);
    if (!object.empty())
    {
        std::size_t pos = object.find_first_not_of(" \t");
        if (pos != std::string::npos)
            object = object.substr(pos);
        else
            object.clear();
    }
    if (verb == "go" || verb == "move")
    {
        if (object.empty())
            std::cout << "Go where?\n";
        else
            move(object);
    }
    else if (verb == "look" || verb == "l")
    {
        look();
    }
    else if (verb == "attack" || verb == "fight")
    {
        attack();
    }
    else if (verb == "pickup" || verb == "get" || verb == "take")
    {
        if (object.empty())
            std::cout << "Pick up what?\n";
        else
            pickupItem(object);
    }
    else if (verb == "inventory" || verb == "i")
    {
        inventory();
    }
    else if (verb == "use")
    {
        if (object.empty())
            std::cout << "Use what?\n";
        else
            useItem(object);
    }
    else if (verb == "equip" || verb == "e")
    {
        if (object.empty())
            std::cout << "Equip what?\n";
        else
            equip(object);
    }
    else if (verb == "stats")
    {
        player->displayStats();
    }
    else if (verb == "help" || verb == "h" || verb == "?")
    {
        help();
    }
    else if (verb == "quit" || verb == "exit")
    {
        game_over = true;
    }
    else
    {
        std::cout << "I don't understand that command.\n";
    }
}

// TODO: Implement move
// HINTS:
// - Check if monster blocks path (current_room->hasMonster())
// - If blocked, print message and return
// - Get exit in specified direction
// - If exit exists:
//   - Update current_room
//   - Display new room
//   - Mark as visited
// - Otherwise print error: "You can't go that way!"
//
void Game::move(const std::string &direction)
{
    // TODO: Move to adjacent room
    if (current_room == NULL)
        return;

    if (current_room->hasMonster())
    {
        std::cout << "A monster blocks your path! Defeat it before moving.\n";
        return;
    }

    Room *next = current_room->getExit(direction);
    if (next != NULL)
    {
        current_room = next;
        look();
    }
    else
    {
        std::cout << "You can't go that way!\n";
    }
}

// TODO: Implement look
// HINTS:
// - Simply display current room
//
void Game::look()
{
    // TODO: Display current room
    if (current_room != NULL)
    {
        current_room->display();
    }
}

// TODO: Implement attack
// HINTS:
// - Check if monster in room
// - If no monster, print message and return
// - If monster present, call combat()
//
void Game::attack()
{
    // TODO: Attack monster in room
    if (current_room == NULL)
        return;
    if (!current_room->hasMonster())
    {
        std::cout << "There is nothing here to attack.\n";
        return;
    }

    Monster *monster = current_room->getMonster();
    if (monster == NULL)
    {
        std::cout << "There is nothing here to attack.\n";
        return;
    }
    combat(monster);
}

// TODO: Implement combat
// HINTS:
// - Print "=== COMBAT BEGINS ==="
// - Combat loop: while both player and monster are alive
//   - Prompt for player action: attack/use <item>/flee
//   - If attack:
//     * Calculate player damage
//     * Monster takes damage
//     * If monster dead:
//       - Print victory
//       - Player gains exp and gold
//       - Get loot from monster
//       - Add loot to current room
//       - Check if Dragon
//       - Clear monster from room
//       - Break from loop
//   - If use:
//     * Extract item name from command
//     * Call player->useItem()
//   - If flee:
//     * Print message and break
//   - Monster turn (if alive):
//     * Print attack message
//     * Calculate monster damage
//     * Player takes damage
// - Print "=== COMBAT ENDS ==="
//
void Game::combat(Monster *monster)
{
    // TODO: Implement turn-based combat
    if (monster == NULL)
        return;
    std::cout << "\n=== COMBAT BEGINS ===\n";

    std::string cmd;
    while (player->isAlive() && monster->isAlive())
    {
        std::cout << "\n";
        player->displayStatus();
        std::cout << " vs ";
        monster->displayStatus();
        std::cout << "\n";

        std::cout << "Choose action (attack/use <item</flee): ";
        if (!std::getline(std::cin, cmd))
            break;

        std::transform(cmd.begin(), cmd.end(), cmd.begin(), [](unsigned char c)
                       { return std::tolower(c); });

        if (cmd == "attack" || cmd == "a")
        {
            int dmg = player->calculateDamage();
            std::cout << "\nYou attack!\n";
            monster->takeDamage(dmg);

            if (!monster->isAlive())
            {
                std::cout << "You defeated the " << monster->getName() << "!\n";
                if (monster->getName() == "Dragon")
                {
                    std::cout << "The Dragon falls with a terrifying roar...\n";
                    victory = true;
                }
                current_room->setMonster(NULL);
                break;
            }
        }
        else if (cmd.rfind("use", 0) == 0)
        {
            std::string item_name = cmd.substr(4);
            std::size_t pos = item_name.find_first_not_of(" \t");
            if (pos != std::string::npos)
                item_name = item_name.substr(pos);
            if (item_name.empty())
            {
                std::cout << "Use what?\n";
            }
            else
            {
                player->useItem(item_name);
            }
        }
        else if (cmd == "flee")
        {
            std::cout << "You flee from combat!\n";
            break;
        }
        else
        {
            std::cout << "Unknown combat command.\n";
        }

        if (monster->isAlive() && player->isAlive())
        {
            std::cout << "\nThe " << monster->getName() << " attacks you!\n";
            int mdmg = monster->calculateDamage();
            player->takeDamage(mdmg);
        }
    }
    std::cout << "=== COMBAT ENDS ===\n";
}

// TODO: Implement pickupItem
// HINTS:
// - Get item from current room
// - If exists:
//   - Add to player inventory
//   - Remove from room (ownership transfer!)
// - Otherwise print error
//
void Game::pickupItem(const std::string &item_name)
{
    // TODO: Pick up item from room
    if (current_room == NULL)
        return;
    Item *item = current_room->getItem(item_name);
    if (item == NULL)
    {
        std::cout << "You don't see \"" << item_name << "\" here.\n";
        return;
    }
    current_room->removeItem(item_name);
    player->addItem(item);

    std::cout << "You pick up " << item->getName() << ".\n";
}

// TODO: Implement inventory
//
void Game::inventory()
{
    // TODO: Display player inventory
    player->displayInventory();
}

// TODO: Implement useItem
// HINTS:
// - Call player->useItem(item_name)
//
void Game::useItem(const std::string &item_name)
{
    // TODO: Use item from inventory
    player->useItem(item_name);
}

// TODO: Implement equip
// HINTS:
// - Get item from player inventory
// - Check if item exists
// - Check item type:
//   - If "Weapon": call player->equipWeapon()
//   - If "Armor": call player->equipArmor()
//   - Otherwise: print error (can't equip consumables)
//
void Game::equip(const std::string &item_name)
{
    // TODO: Equip weapon or armor
    Item *item = player->getItem(item_name);
    if (item == NULL)
    {
        std::cout << "You don't have \"" << item_name << "\".\n";
        return;
    }

    std::string type = item->getType();
    if (type == "Weapon")
    {
        player->equipWeapon(static_cast<Weapon *>(item));
        std::cout << "You equip " << item->getName() << ".\n";
    }
    else if (type == "Armor")
    {
        player->equipArmor(static_cast<Armor *>(item));
        std::cout << "You equip " << item->getName() << ".\n";
    }
    else
    {
        std::cout << "You can't equip that.\n";
    }
}

// TODO: Implement help
// HINTS:
// - Print all available commands with descriptions
// - Format nicely with headers
// - Commands:
//   * go <direction> - Move
//   * look - Look around
//   * attack - Attack monster
//   * pickup <item> - Pick up item
//   * inventory - Show inventory
//   * use <item> - Use consumable
//   * equip <item> - Equip weapon/armor
//   * stats - Show character stats
//   * help - Show this help
//   * quit - Exit game
//
void Game::help()
{
    // TODO: Display help message
    std::cout << "\n=== Commands ===\n";
    std::cout << "  go <direction>   - Move north, south, east, or west\n";
    std::cout << "  look             - Look around the current room\n";
    std::cout << "  attack           - Attack the monster in the room\n";
    std::cout << "  pickup <item>    - Pick up an item from the room\n";
    std::cout << "  inventory        - Show your inventory\n";
    std::cout << "  use <item>       - Use a consumable item\n";
    std::cout << "  equip <item>     - Equip a weapon or armor\n";
    std::cout << "  stats            - Show your character stats\n";
    std::cout << "  help             - Show this help message\n";
    std::cout << "  quit             - Exit the game\n";
}
