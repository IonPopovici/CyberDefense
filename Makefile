CXX := g++
CXXFLAGS := -std=c++14 -Wall -Wextra -pedantic
TARGET := cyber_defense

SOURCES := main.cpp Engine.cpp Renderer.cpp Listener.cpp GameTypes.cpp
OBJECTS := $(SOURCES:.cpp=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)
