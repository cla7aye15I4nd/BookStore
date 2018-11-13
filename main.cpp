#include <cstring>
#include <iostream>

int main() {
    std::string s;
    std::cin >> s;
    for (auto c : s)
        std::cout << int(c) << ' ';
    std::cerr << sizeof (char) << '\n';
}
