CXX = g++
CXXFLAGS = -std=c++14 -Wall -O3

make : clean code

clean:
	rm code -f
code: bookstore.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS)
