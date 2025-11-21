# Build Instructions for RPG Lab

This document explains how to compile, run, and test your RPG game.

---

## Prerequisites

It is **highly recommended** to use the ECE linux servers for this project,
whether you log into them directly or use them as a backend for your VSCode GUI
running locally.  The project is NOT designed to run on Windows natively, and
while it may be possible to get it working using WSL or MinGW, you may run into
unexpected issues.


### Verify Installation

```bash
# Check compiler
g++ --version

# Check make
make --version

# Check valgrind 
valgrind --version
```

---

## Project Structure

Your project should have the following files:

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

---

## Basic Build Commands

### Compile the Project

```bash
make
```

This will:
1. Compile all .cpp files into .o object files
2. Link object files into executable `dungeon_rpg` in the `bin/` directory
3. Display any compilation errors or warnings

**Expected output**:
```
g++ -c -std=c++98 -Wall -Wextra -Werror -g src/main.cpp
g++ -c -std=c++98 -Wall -Wextra -Werror -g src/Character.cpp
g++ -c -std=c++98 -Wall -Wextra -Werror -g src/Player.cpp
...
g++ -o bin/dungeon_rpg src/main.o src/Character.o src/Player.o src/Monster.o src/Item.o src/Room.o src/Game.o
```

### Run the Game

```bash
./bin/dungeon_rpg
```


### Clean Build Files

```bash
make clean
```

This removes all compiled object files (.o) and the executable, giving you a fresh start.

### Rebuild from Scratch

```bash
make clean
make
```

---

### Compiler Flags Explained

- `-std=c++98`: Use C++98 standard (compatible with older systems)
- `-Wall`: Enable all warnings
- `-Wextra`: Enable extra warnings
- `-Werror`: Treat warnings as errors (forces clean code)
- `-g`: Include debugging symbols (for gdb)

---

## Compilation Process

### Step-by-Step

1. **Preprocessing**: Expands #include directives
   ```bash
   g++ -E src/Character.cpp > src/Character.i
   ```

2. **Compilation**: Converts to assembly
   ```bash
   g++ -S src/Character.cpp
   ```

3. **Assembly**: Creates object file
   ```bash
   g++ -c src/Character.cpp -o src/Character.o
   ```

4. **Linking**: Combines object files into executable
   ```bash
   g++ -o bin/dungeon_rpg src/main.o src/Character.o src/Player.o ...
   ```

The Makefile automates all these steps!

---

## Common Compilation Errors

### Error: "undefined reference to vtable"

**Meaning**: You declared a virtual function but didn't implement it.

**Example**:
```cpp
// In Character.h
virtual void displayStats() const;

// Missing in Character.cpp!
```

**Fix**: Implement all virtual functions:
```cpp
// In Character.cpp
void Character::displayStats() const {
    std::cout << name << " [HP: " << current_hp << "]" << std::endl;
}
```

---

### Error: "no matching function for call to constructor"

**Meaning**: Derived class constructor doesn't call base class constructor.

**Example**:
```cpp
Player::Player(const std::string& name) {  // ERROR!
    level = 1;
}
```

**Fix**: Use initializer list:
```cpp
Player::Player(const std::string& name) 
    : Character(name, 100, 10, 5) {  // Call base constructor
    level = 1;
}
```

---

### Error: "'X' was not declared in this scope"

**Meaning**: Missing #include or forward declaration.

**Example**:
```cpp
// In Game.cpp
Player* p = new Player("Hero");  // ERROR if Player.h not included
```

**Fix**: Add include:
```cpp
#include "Player.h"
```

---

### Error: "multiple definition of 'X'"

**Meaning**: Function defined in header file without `inline`.

**Problem**:
```cpp
// In Character.h
void Character::displayStats() const {  // ERROR!
    std::cout << name << std::endl;
}
```

**Fix**: Define in .cpp file:
```cpp
// In Character.cpp
void Character::displayStats() const {
    std::cout << name << std::endl;
}
```

---

### Warning: "unused variable"

**Meaning**: Declared variable but never used.

**Example**:
```cpp
void func() {
    int x = 5;  // Never used
}
```

**Fix**: Remove or use the variable, or cast to void:
```cpp
(void)x;  // Explicitly mark as intentionally unused
```

---

## Debugging

### Using GDB (GNU Debugger)

**Compile with debug symbols** (already done with -g flag):
```bash
make
```

**Run under debugger**:
```bash
gdb ./bin/dungeon_rpg
```

**GDB Commands**:
```
(gdb) run                    # Run program
(gdb) break main             # Set breakpoint at main
(gdb) break Game.cpp:50      # Set breakpoint at line 50
(gdb) next                   # Execute next line
(gdb) step                   # Step into function
(gdb) continue               # Continue execution
(gdb) print variable         # Print variable value
(gdb) backtrace              # Show call stack
(gdb) quit                   # Exit gdb
```

**Example debugging session**:
```bash
$ gdb ./bin/dungeon_rpg
(gdb) break main
Breakpoint 1 at 0x1234: file main.cpp, line 5.
(gdb) run
Starting program: ./bin/dungeon_rpg
Breakpoint 1, main () at main.cpp:5
(gdb) next
(gdb) print game
(gdb) continue
```

---

### Using Valgrind (Memory Leak Detection)

**Run with valgrind**:
```bash
valgrind --leak-check=full --show-leak-kinds=all ./bin/dungeon_rpg
```

**What to look for**:
```
HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks
  total heap usage: 100 allocs, 100 frees, 10,000 bytes allocated

All heap blocks were freed -- no leaks are possible
```

**If you see leaks**:
```
LEAK SUMMARY:
   definitely lost: 240 bytes in 3 blocks
```

This means you allocated memory with `new` but forgot to `delete` it!

**Finding the leak**:
Valgrind shows where memory was allocated:
```
240 bytes in 3 blocks are definitely lost in loss record 1 of 1
   at 0x1234: operator new(unsigned long) (vg_replace_malloc.c:334)
   by 0x5678: Player::addItem(Item*) (Player.cpp:45)
   by 0x9ABC: Game::run() (Game.cpp:123)
```

Check line 45 in Player.cpp - you're creating an Item but not deleting it!

---

### Adding Debug Output

**Temporary debug prints**:
```cpp
void Player::addItem(Item* item) {
    std::cout << "DEBUG: Adding item " << item->getName() << std::endl;
    inventory.push_back(item);
    std::cout << "DEBUG: Inventory size now: " << inventory.size() << std::endl;
}
```

**Remember to remove debug output before submission!**

---

## Testing Strategy

### Week 1: Unit Testing

Create simple test programs for each class:

**test_character.cpp**:
```cpp
#include "Character.h"
#include <iostream>

int main() {
    Character hero("Hero", 100, 10, 5);
    hero.displayStats();
    hero.takeDamage(30);
    hero.heal(10);
    return 0;
}
```

**Compile and run**:
```bash
g++ -o test_character test_character.cpp Character.cpp
./test_character
```

### Week 2: Integration Testing

Test class interactions:

**test_player_inventory.cpp**:
```cpp
#include "Player.h"
#include "Item.h"

int main() {
    Player p("Bob");
    p.addItem(new Weapon("Sword", "Sharp", 5));
    p.displayInventory();
    p.equipWeapon("sword");
    // ... more tests
    return 0;
}
```

### Week 3: System Testing

Test the complete game:

1. **Functional tests**:
   - Can move between rooms?
   - Can pick up items?
   - Can fight monsters?
   - Can win game?

2. **Edge cases**:
   - What if player tries to go invalid direction?
   - What if player tries to pick up non-existent item?
   - What if player tries to use non-consumable?

3. **Memory tests**:
   ```bash
   valgrind --leak-check=full ./bin/dungeon_rpg
   ```
   Play through game and quit normally - should show no leaks.


## Performance Tips

### Optimization Flags

For faster execution (after debugging):
```makefile
CXXFLAGS = -std=c++98 -Wall -O2  # Remove -g, add -O2
```

**Note**: Only use optimization for final version, not during development!

### Profiling

To find slow code:
```bash
g++ -pg -o bin/dungeon_rpg src/main.cpp ...  # Compile with profiling
./bin/dungeon_rpg                         # Run normally
gprof bin/dungeon_rpg gmon.out > analysis.txt  # Analyze
```

---

## Submission Build

Before submitting:

1. **Clean build**:
   ```bash
   make clean
   make
   ```

2. **Test run**:
   ```bash
   ./bin/dungeon_rpg
   ```
   Play through and ensure it works!

3. **Memory check**:
   ```bash
   valgrind --leak-check=full ./bin/dungeon_rpg
   ```
   Should show no leaks!

4. **Remove debug output**: Delete any debug print statements

5. **Check warnings**: Should compile with zero warnings

6. **Verify files**: Ensure all required files are present

---

## Getting Help

If you have build issues:

1. **Read error messages carefully** - they usually tell you exactly what's wrong
2. **Check TODO.md** for implementation guidance
3. **Try clean rebuild**: `make clean && make`
4. **Check file permissions**: `ls -l`
5. **Verify all files present**: `ls *.h *.cpp`
6. **Ask for help**: Office hours, Ed Discussion, etc. 

---

## Summary of Commands

```bash
# Build
make                    # Compile project
make clean              # Remove compiled files
make clean && make      # Clean rebuild

# Run
./bin/dungeon_rpg              # Run game

# Debug
gdb ./bin/dungeon_rpg          # Debug with GDB
valgrind --leak-check=full ./bin/dungeon_rpg  # Check memory leaks
```

---

**You're ready to build! Good luck!**
