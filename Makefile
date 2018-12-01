CXX = g++
CXXFLAGS = -std=c++14 -Wall -O3

code: bookstore.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS)
clean:
	rm code -f
