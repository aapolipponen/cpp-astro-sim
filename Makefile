# Compiler
CXX = g++

# Compiler flags
CXXFLAGS =

# Linker flags
LDFLAGS =

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
