CXX = g++
CXXFLAGS = -std=c++20 -Wall -Iinclude

SRC = src/main.cpp src/device/*.cpp src/net/*.cpp src/debug/*.cpp src/core/*.cpp
OUT = backInput

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)
	$(CXX) $(CXXFLAGS) src/asker_test.cpp -o ask_test
clean:
	rm -f $(OUT)
	rm -f ask_test