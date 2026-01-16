# Compiler and Flags
CXX = g++
CXXFLAGS = -w -I"./SDL2-2.0.10/include"
LDFLAGS = -L"./.libraries" -lmingw32 -lSDL2main -lSDL2 -mconsole -lole32 -loleaut32 -limm32 -lwinmm -lgdi32 -lsetupapi -lversion

# Folders
SRC_DIR = .
BUILD_DIR = build

# Files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
# Objects go into the build folder
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
# The EXE stays in the main (root) folder
TARGET = main.exe

# Default Rule
all: $(BUILD_DIR) $(TARGET)

# 1. Create the build directory if it doesn't exist
$(BUILD_DIR):
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

# 2. Link the object files from 'build' into the final EXE in root
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# 3. Compile .cpp files into .o files inside the 'build' folder
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	@if exist $(BUILD_DIR) rd /s /q $(BUILD_DIR)
	@if exist $(TARGET) del $(TARGET)