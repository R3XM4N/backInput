CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC = src/main.cpp src/controls/virt_global.cpp src/controls/devices/*.cpp src/net/*.cpp src/system/*.cpp
OUT = backInput

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)
	$(CXX) $(CXXFLAGS) src/asker_test.cpp -o ask_test
clean:
	rm -f $(OUT)
	rm -f ask_test