// Completed Game.cpp with all TODOs and comments preserved
#include "Game.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// TODO: Implement Game constructor
Game::Game() : player(NULL), current_room(NULL),
               game_over(false), victory(false)
{
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

    for (std::map<std::string, Room*>::iterator it = world.begin(); it != world.end(); ++it){
        delete it->second;
    }
    world.clear();
}

// TODO: Implement initializeWorld
void Game::initializeWorld()
{
    // TODO: Create rooms
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

    // TODO: Add monsters (using derived monster classes)
    world["Hallway"]->setMonster(new Goblin());
    world["Armory"]->setMonster(new Skeleton());
    world["Treasury"]->setMonster(new Skeleton());
    world["Throne Room"]->setMonster(new Dragon());

    // TODO: Add items
    world["Entrance"]->addItem(new Consumable("Small Potion", "A small potion that restores health.", 10));
    world["Armory"]->addItem(new Weapon("Iron Sword", "A solid iron sword.", 30));
    world["Armory"]->addItem(new Armor("Chain Mail", "Sturdy chain mail armor.", 20));
    world["Treasury"]->addItem(new Consumable("Health Potion", "A potion that restores HP.", 20));

    // TODO: Set starting room
    current_room = entrance;
    current_room->setVisited(true);
}

// TODO: Implement createStartingInventory
void Game::createStartingInventory()
{
    player->addItem(new Weapon("Rusty Dagger", "An old, dull dagger.", 2));
    player->addItem(new Consumable("Bread", "A small loaf of bread.", 5));
    player->addItem(new Weapon("Dragon Slayer", "Ultimate OP sword", 100));
}

// TODO: Implement addRoom
void Game::addRoom(Room *room)
{
    if (room == NULL)
        return;
    world[room->getName()] = room;
}

// TODO: Implement connectRooms
void Game::connectRooms(const std::string &room1_name, const std::string &direction, const std::string &room2_name)
{
    std::map<std::string, Room*>::iterator it1 = world.find(room1_name);
    std::map<std::string, Room*>::iterator it2 = world.find(room2_name);

    if (it1 == world.end() || it2 == world.end())
        return;

    Room* r1 = it1->second;
    Room* r2 = it2->second;

    //forward
    r1->addExit(direction, r2);
    //reverse
    std::string rev;
    if (direction == "north") rev = "south";
    else if (direction == "south") rev = "north";
    else if (direction == "east") rev = "west";
    else if (direction == "west") rev = "east";

    if (!rev.empty())
        r2->addExit(rev, r1);
}

// TODO: Implement run
void Game::run()
{
    std::cout << "====================================\n";
    std::cout << "       DUNGEON ADVENTURE GAME       \n";
    std::cout << "====================================\n\n";

    std::string name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    if (name.empty()) name = "Hero";

    player = new Player(name);

    initializeWorld();
    createStartingInventory();

    look();

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

        std::cout << "\n> ";

        std::string line;
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;

        std::transform(line.begin(), line.end(), line.begin(), ::tolower);

        processCommand(line);
    }

    std::cout << "\nGame over.\n";
}

// TODO: Implement processCommand
void Game::processCommand(const std::string &command)
{
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
        if (object.empty()) std::cout << "Go where?\n";
        else move(object);
    }
    else if (verb == "look" || verb == "l")
        look();
    else if (verb == "attack" || verb == "fight")
        attack();
    else if (verb == "pickup" || verb == "get" || verb == "take")
    {
        if (object.empty()) std::cout << "Pick up what?\n";
        else pickupItem(object);
    }
    else if (verb == "inventory" || verb == "i")
        inventory();
    else if (verb == "use")
    {
        if (object.empty()) std::cout << "Use what?\n";
        else useItem(object);
    }
    else if (verb == "equip" || verb == "e")
    {
        if (object.empty()) std::cout << "Equip what?\n";
        else equip(object);
    }
    else if (verb == "stats")
        player->displayStats();
    else if (verb == "help" || verb == "h" || verb == "?")
        help();
    else if (verb == "quit" || verb == "exit")
        game_over = true;
    else
        std::cout << "I don't understand that command.\n";
}

// TODO: Implement move
void Game::move(const std::string &direction)
{
    if (current_room == NULL) return;

    if (current_room->hasMonster())
    {
        std::cout << "A monster blocks your path! Defeat it first.\n";
        return;
    }

    Room *next = current_room->getExit(direction);
    if (next != NULL)
    {
        current_room = next;
        current_room-> setVisited(true);
        look();
    }
    else
        std::cout << "You can't go that way!\n";
}

// TODO: Implement look
void Game::look()
{
    if (current_room != NULL)
        current_room->display();
}

// TODO: Implement attack
void Game::attack()
{
    if (current_room == NULL) return;

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
void Game::combat(Monster *monster)
{
    if (monster == NULL) return;

    std::cout << "\n=== COMBAT BEGINS ===\n";

    std::string cmd;
    while (player->isAlive() && monster->isAlive())
    {
        std::cout << "\n";
        player->displayStatus();
        std::cout << " vs ";
        monster->displayStatus();
        std::cout << "\n";

        std::cout << "Choose action (attack/use <item>/flee): ";
        if (!std::getline(std::cin, cmd)) break;

        std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

        if (cmd == "attack" || cmd == "a")
        {
            int dmg = player->calculateDamage();
            std::cout << "\nYou attack!\n";
            monster->takeDamage(dmg);

            if (!monster->isAlive())
            {
                std::cout << "You defeated the " << monster->getName() << "!\n";

                // Rewards
                player->gainExperience(monster->getExperienceReward());
                player->addGold(monster->getGoldReward());

                // Loot
                std::vector<Item*> loot = monster->dropLoot();
                for (std::vector<Item*>::iterator it = loot.begin(); it != loot.end(); ++it)
                {
                    current_room->addItem(*it);
                }

                if (monster->getName() == "Dragon")
                {
                    std::cout << "The Dragon collapses... You are victorious!\n";
                    victory = true;
                }

                current_room->clearMonster();
                break;
            }
        }
        else if (cmd.rfind("use", 0) == 0)
        {
            std::string item_name = cmd.substr(4);
            std::size_t pos = item_name.find_first_not_of(" \t");
            if (pos != std::string::npos)
                item_name = item_name.substr(pos);

            if (item_name.empty()) std::cout << "Use what?\n";
            else player->useItem(item_name);
        }
        else if (cmd == "flee")
        {
            std::cout << "You flee from combat!\n";
            break;
        }
        else
            std::cout << "Unknown combat command.\n";

        if (monster->isAlive() && player->isAlive())
        {
            std::cout << "\n" << monster->getAttackMessage() << "\n";
            int mdmg = monster->calculateDamage();
            player->takeDamage(mdmg);
        }
    }

    std::cout << "=== COMBAT ENDS ===\n";
}

// TODO: Implement pickupItem
void Game::pickupItem(const std::string &item_name)
{
    if (current_room == NULL) return;

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
void Game::inventory()
{
    player->displayInventory();
}

// TODO: Implement useItem
void Game::useItem(const std::string &item_name)
{
    player->useItem(item_name);
}

// TODO: Implement equip
void Game::equip(const std::string &item_name)
{
    Item *item = player->getItem(item_name);
    if (item == NULL)
    {
        std::cout << "You don't have \"" << item_name << "\".\n";
        return;
    }

    std::string type = item->getType();
    if (type == "Weapon")
    {
        player->equipWeapon(item_name);
    }
    else if (type == "Armor")
    {
        player->equipArmor(item_name);
    }
    else
    {
        std::cout << "You can't equip that.\n";
    }
}

// TODO: Implement help
void Game::help()
{
    std::cout << "\n=== Commands ===\n";
    std::cout << "  go <direction>   - Move north, south, east, or west\n";
    std::cout << "  look             - Look around the room\n";
    std::cout << "  attack           - Attack a monster\n";
    std::cout << "  pickup <item>    - Pick up an item\n";
    std::cout << "  inventory        - Show inventory\n";
    std::cout << "  use <item>       - Use a consumable\n";
    std::cout << "  equip <item>     - Equip a weapon or armor\n";
    std::cout << "  stats            - Show character stats\n";
    std::cout << "  help             - Show this help\n";
    std::cout << "  quit             - Exit game\n";
}