CXX = g++
CXXFLAGS = -std=c++14 -Wall -O3
APILIB = rem/bookstore.a
make : clean code copy

clean:
	rm code -f
code: main.cpp
	$(CXX) -o $@ $^ $(APILIB) $(CXXFLAGS)
copy:
	cp code judge/bookstore
