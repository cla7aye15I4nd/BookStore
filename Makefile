CXX = g++
CXXFLAGS = -std=c++14 -Wall -O2 

code: bookstore.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS)
clean:
	rm code -f
