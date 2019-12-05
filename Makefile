CXX = g++
CXXFLAGS = -std=c++14 -Wall -O3
APILIB = rem/bookstore.a
make : clean code

clean:
	rm code -f
code: main.cpp
	$(CXX) -o $@ $^ -DUSER $(CXXFLAGS)
copy:
	cp code tmp/bookstore
