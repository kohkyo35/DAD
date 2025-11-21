# Dungeon Crawler RPG - Lab Assignment

## Overview

You will implement a text-based RPG game in C++ that demonstrates object-oriented programming principles including:
- Class design and encapsulation
- Inheritance hierarchies
- Polymorphism with virtual functions
- Dynamic memory management
- STL containers (vector, string, map)
- Resource management with destructors (RAII)

## Learning Objectives

By completing this lab, you will:
1. Transition from C-style to C++-style programming
2. Design and implement class hierarchies
3. Use virtual functions for runtime polymorphism
4. Manage dynamic memory safely with new/delete
5. Use STL containers effectively
6. Apply RAII principles for resource management
7. Organize multi-file C++ projects

## Game Description

Players navigate through a dungeon, fighting monsters, collecting items, and gaining experience. The game features:
- Multiple room exploration
- Turn-based combat system
- Inventory management with weapons and armor
- Character progression (leveling up)
- Different monster types with unique behaviors
- Victory condition (defeat the final boss)

## Project Structure

```
starter_code/
├── Documentation
├──── README.md              # This file
├──── TODO.md                # Detailed implementation tasks
├──── BUILD_INSTRUCTIONS.md  # How to compile and run
│
├── Makefile                 # Makefile for build system
│
├── bin 
├──── dungeon_rpg.solution       # Fully compiled executable for testing and
│                              reference (will run on mario.ece.utexas.edu)
│
│
├── include
├──── Character.h            # Base character class
├──── Player.h               # Player class (inherits Character)
├──── Monster.h              # Monster hierarchy
├──── Item.h                 # Item hierarchy
├──── Room.h                 # Room class
├──── Game.h                 # Game controller
│
├── src
├──── Character.cpp          # Character class implementation
├──── Player.cpp             # Player class implementation
├──── Monster.cpp            # Monster classes implementation
├──── Item.cpp               # Item classes implementation
├──── Room.cpp               # Room class implementation
├──── Game.cpp               # Game controller implementation
└──── main.cpp               # Entry point
```

## Class Hierarchy

### Character Hierarchy
```
Character (base)
├── Player (adds level, experience, inventory)
└── Monster (adds rewards, loot)
    ├── Goblin
    ├── Skeleton
    └── Dragon (boss)
```

### Item Hierarchy
```
Item (base)
├── Weapon (increases attack)
├── Armor (increases defense)
└── Consumable (healing items)
```

### Other Classes
- **Room**: Represents locations, contains monsters and items
- **Game**: Main controller, manages game state and world

## Implementation Timeline

### Week 1: Basic Classes (After Lectures 1-2)
**Concepts**: Classes, constructors/destructors, encapsulation, new/delete, vector, string

**Tasks**:
- Implement Character base class
- Implement Item base class and derived classes
- Create basic inventory management
- Test with simple programs

**Time Estimate**: 6-8 hours

### Week 2: Inheritance and Polymorphism (After Lectures 3-4)
**Concepts**: Inheritance, virtual functions, constructor chaining, polymorphism

**Tasks**:
- Implement Player class
- Implement Monster hierarchy
- Add virtual functions for combat
- Test polymorphic behavior

**Time Estimate**: 8-10 hours

### Week 3: Integration (After Lecture 5)
**Concepts**: std::map, composition, object ownership, complete system design

**Tasks**:
- Implement Room class
- Implement Game class with world management
- Connect all components
- Add command processing
- Test complete game

**Time Estimate**: 10-12 hours

**Total Estimated Time**: 24-30 hours

## Getting Started

1. **Read through all provided files** to understand the structure
2. **Start with TODO.md** for detailed implementation tasks
3. **Follow the week-by-week guides** (WEEK1_CONCEPTS.md, etc.)
4. **Build incrementally** - test each component before moving on
5. **Use the provided Makefile** to compile your code

## Building the Project

See [BUILD_INSTRUCTIONS.md](BUILD_INSTRUCTIONS.md) for detailed compilation instructions.

Quick start:
```bash
make           # Compile the project
./bin/dungeon_rpg     # Run the game
make clean     # Remove compiled files
```

## Testing Strategy

### Unit Testing Approach
1. **Week 1**: Test each class independently
   - Create test programs for Character, Item classes
   - Verify constructors, destructors, methods work correctly

2. **Week 2**: Test inheritance and polymorphism
   - Create arrays of base class pointers
   - Verify virtual functions call correct implementations
   - Test monster-specific behaviors

3. **Week 3**: Integration testing
   - Test room connections
   - Test combat system end-to-end
   - Test inventory management
   - Play through the entire game

### Memory Testing
Use valgrind to check for memory leaks:
```bash
make
valgrind --leak-check=full ./bin/dungeon_rpg
```

All memory should be properly freed - no leaks!

## Common Issues and Solutions

### Compilation Errors

**"undefined reference to vtable"**
- You declared a virtual function but didn't implement it
- Make sure all virtual functions have definitions

**"no matching function for call to constructor"**
- Forgot to call base class constructor in derived class
- Use initializer list: `Derived() : Base(args) { }`

**"error: 'X' was not declared in this scope"**
- Missing #include directive
- Check header dependencies

### Runtime Errors

**Segmentation fault**
- Dereferencing NULL pointer
- Add NULL checks before using pointers
- Use debugger: `gdb ./bin/dungeon_rpg`

**Memory leaks**
- Not deleting dynamically allocated objects
- Check all destructors clean up properly
- Run valgrind to find leaks

**Virtual function not being called**
- Need pointer or reference to base class
- Make sure function is declared virtual in base class


## Extensions (Optional - up to 20 extra credit points)

Once you have the basic game working, consider adding:
- Save/load game functionality
- More monster types with special abilities
- More item types (keys, scrolls, etc.)
- Character classes (Warrior, Mage, Rogue)
- More complex combat mechanics
- Shop system
- Quest system
- Multiple endings

## Resources

### C++ References
- [cppreference.com](https://en.cppreference.com/) - Comprehensive C++ reference
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) - Best practices

### Debugging
- GDB tutorial: `gdb ./bin/dungeon_rpg`, then `run`, `bt` (backtrace), `print variable`
- Valgrind for memory: `valgrind --leak-check=full ./bin/dungeon_rpg`

### Getting Help
- Office hours
- Course forum: Ed Discussion 
- Study groups strongly encouraged!

## Submission

Submit the following:
1. All source files (.h and .cpp)
2. Makefile
3. README.md (updated with any changes you made)
4. Any additional documentation
5. Test output showing your game works
6. Valgrind output showing no memory leaks

**Deadline**: December 10, 2025 @ 11:59pm 

## Academic Integrity

- You may discuss concepts with classmates
- You may help each other debug
- **You may NOT share code directly**
- **You may NOT copy code from online sources**
- **Write your own implementations**
- **Any use of AI tools must be disclosed and cited appropriately**


**Good luck, and have fun building your RPG!**
