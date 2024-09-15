# Compiler and flags
CXX := g++
C := gcc
CXXFLAGS := -Wall -std=c++17  # Add any flags you need
CFLAGS := -Wall  # Add any C-specific flags
LDFLAGS := `pkg-config --cflags --libs sdl2` -lOpenCL  # Link SDL2 and OpenCL

# Source files and object files
SRCS_CPP := ConsoleInputs.cpp clIntegration.cpp GameObject.cpp SerializeString.cpp \
            RevenantMesh.cpp main.cpp
SRCS_C := RevenantVectors.c RevenantTris.c
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
