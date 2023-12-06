# compilers
CXX = g++
CC = gcc

# compiler flag
CXXFLAGS = -std=c++14 -Iinclude -I../glad/include -I../thirdparty/glm
CFLAGS = -I../glad/include

# linker flag
LDFLAGS = -lSDL2 -ldl

# Source files for C++
CPP_SRC = $(wildcard src/*.cc)
# Object files for C++
CPP_OBJ = $(CPP_SRC:src/%.cc=build/%.o)

# Source file for C (glad.c)
C_SRC = ../glad/src/glad.c
# Object file for C
C_OBJ = build/glad.o

# Object files combined
OBJ = $(CPP_OBJ) $(C_OBJ)

# Output binary
BIN = a.out

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $(BIN)

# Create object files directory
build:
	mkdir -p build

# Rule for creating object files for C++
build/%.o: src/%.cc | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for compiling glad.c (C file)
build/glad.o: $(C_SRC) | build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(BIN)

.PHONY: all clean
