# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11 -I/data/data/com.termux/files/usr/include/SDL2 -I/data/data/com.termux/files/usr/include -DNO_SHARED_MEMORY -D_REENTRANT -D_THREAD_SAFE

# Linker flags
LDFLAGS = -L/data/data/com.termux/files/usr/lib -lSDL2

# Source files
SOURCES = main.cpp particle.cpp Vector2D.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Target executable
TARGET = bin

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $^ $(LDFLAGS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
