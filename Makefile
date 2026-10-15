CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -g -MMD -MP -Iinclude
LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm -mconsole
MINGW_BIN = $(shell dirname "$$(command -v $(CXX))")

TARGET = build/TingoBingo_3D_V1.exe
RUNTIME_DLLS = build/libraylib.dll build/glfw3.dll

# Find all C++ source files, including those in subdirectories.
SRC = $(shell find src -name "*.cpp")

# Generate a corresponding object file path for each source file.
OBJ = $(patsubst src/%.cpp, build/%.o, $(SRC))

.PHONY: all clean run

all: run

$(TARGET): $(OBJ) $(RUNTIME_DLLS)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

# Package raylib's runtime dependencies next to the executable.
build/%.dll: $(MINGW_BIN)/%.dll
	cp "$<" "$@"

# Compile source files while preserving their directory structure.
build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ:.o=.d) $(TARGET) $(RUNTIME_DLLS)

run: $(TARGET)
	./$(TARGET)

-include $(OBJ:.o=.d)