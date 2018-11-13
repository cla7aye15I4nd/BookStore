#include <iostream>
#include "SHA256.hpp"

int main(int argc, char **argv) {
    if (argc > 1)
        std::cout << rem::sha256sum(argv[1]) << std::endl;
    return 0;
}
