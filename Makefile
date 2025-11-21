# Makefile for RPG Lab
# 
# This Makefile automates compilation of the RPG game.
# 
# Usage:
#   make           - Compile the entire project
#   make clean     - Remove all compiled files
#   make rebuild   - Clean and rebuild from scratch

# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++98 -Wall -g
SRC_DIR = src
INC_DIR = include
OUT_DIR = bin

# Executable name
EXECUTABLE = rpg_game

# Source files (all .cpp files)
SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/Character.cpp \
          $(SRC_DIR)/Player.cpp \
          $(SRC_DIR)/Monster.cpp \
          $(SRC_DIR)/Item.cpp \
          $(SRC_DIR)/Room.cpp \
          $(SRC_DIR)/Game.cpp

# Object files (automatically generated from source files)
OBJECTS = $(SOURCES:.cpp=.o)

# Header files (for dependency tracking)
HEADERS = $(INC_DIR)/Character.h \
          $(INC_DIR)/Player.h \
          $(INC_DIR)/Monster.h \
          $(INC_DIR)/Item.h \
          $(INC_DIR)/Room.h \
          $(INC_DIR)/Game.h

# Default target - builds the executable
all: $(EXECUTABLE)

# Link object files into executable
$(EXECUTABLE): $(OBJECTS)
	@echo "Linking..."
	$(CXX) -o $(OUT_DIR)/$@ $^
	@echo "Build complete! Run with: ./$(OUT_DIR)/$(EXECUTABLE)"

# Compile .cpp files into .o object files
# Pattern rule: %.o matches any .o file, %.cpp matches corresponding .cpp file
%.o: %.cpp $(HEADERS)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean up compiled files
clean:
	@echo "Cleaning build files..."
	rm -f $(OBJECTS) $(OUT_DIR)/$(EXECUTABLE)
	@echo "Clean complete!"

# Rebuild from scratch
rebuild: clean all

# Help target - show available commands
help:
	@echo "Available targets:"
	@echo "  make          - Build the project (default)"
	@echo "  make clean    - Remove compiled files"
	@echo "  make rebuild  - Clean and rebuild"
	@echo "  make help     - Show this help message"

# Phony targets (not real files)
.PHONY: all clean rebuild help

# Dependencies (which .cpp files include which .h files)
# These ensure files are recompiled when headers change

main.o: main.cpp Game.h

Character.o: Character.cpp Character.h

Player.o: Player.cpp Player.h Character.h Item.h

Monster.o: Monster.cpp Monster.h Character.h Item.h

Item.o: Item.cpp Item.h

Room.o: Room.cpp Room.h Monster.h Item.h Character.h

Game.o: Game.cpp Game.h Player.h Room.h Monster.h Item.h Character.h
