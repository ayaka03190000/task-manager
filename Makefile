CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra
TARGET=task-manager
SRC=main.cpp

all: $(TARGET)
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
clean:
	rm -f $(TARGET)tasks.txt
.PHONY: all clean
