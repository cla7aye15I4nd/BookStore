CXX = g++
CXXFLAGS = -std=c++14 -Wall -O3

make : clean code copy

clean:
	rm code -f
code: bookstore.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS)
copy:
	cp code judge/bookstore
