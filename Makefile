CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -g -Iinclude
LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm -mconsole

TARGET = build/TingoBingo_3D_V1.exe

# Find all C++ source files, including those in subdirectories.
SRC = $(shell find src -name "*.cpp")

# Generate a corresponding object file path for each source file.
OBJ = $(patsubst src/%.cpp, build/%.o, $(SRC))

.PHONY: all clean run

all: run

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

# Compile source files while preserving their directory structure.
build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)