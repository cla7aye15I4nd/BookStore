#include "bookstore.hpp"
#include <iostream>

sjtu::bookstore bookstore;
int main() {
    if (fopen("command.txt", "r"))
        freopen("command.txt", "r", stdin);
    bookstore.run();
    return 0;
}
