# Compiler and flags
CXX := g++
C := gcc
CXXFLAGS := -Wall -std=c++17 -I./src/headers/cpp -I./src/headers/c # Add any flags you need
CFLAGS := -Wall -I./src/headers/c# Add any C-specific flags
LDFLAGS := `pkg-config --cflags --libs sdl2` -lOpenCL  # Link SDL2 and OpenCL

# Source files and object files
SRCS_CPP := src/ConsoleInputs.cpp src/clIntegration.cpp src/SerializeString.cpp \
            src/RevenantMesh.cpp src/main.cpp src/LobLib.cpp
SRCS_C := src/RevenantVectors.c src/RevenantTris.c
OBJS := $(SRCS_CPP:.cpp=.o) $(SRCS_C:.c=.o)

# Executable name
TARGET := rev

# Default rule
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Rule to compile individual C++ source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile individual C source files
%.o: %.c
	$(C) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild rule
rebuild: clean all
