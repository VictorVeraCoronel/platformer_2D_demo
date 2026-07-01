# ==============================================================================
# COMPILER AND FLAG SETTINGS
# ==============================================================================
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O3

LDFLAGS  := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# ==============================================================================
# FOLDERS AND AUTOMATIC FILE SEARCHING
# ==============================================================================
TARGET   := game.app

# Recursive system compilation
SRCS     := main.cpp $(wildcard systems/logic/*.cpp) $(wildcard systems/render/*.cpp) $(wildcard loaders/*.cpp) $(wildcard spawners/*.cpp)

# Conversion from cpp to .o files
OBJ_DIR  := build
OBJS     := $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

# ==============================================================================
# COMPILER RULES
# ==============================================================================

# Default
all: $(TARGET)

# Executable link
$(TARGET): $(OBJS)
	@echo "=> Enlazando el ejecutable final: $(TARGET)"
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Source code to .o
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "-> Compilando: $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleaning
clean:
	@echo "=> Limpiando archivos temporales..."
	rm -rf $(OBJ_DIR) $(TARGET)

# Avoid conflicts
.PHONY: all clean
