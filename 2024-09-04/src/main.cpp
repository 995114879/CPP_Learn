#include <iostream>

#include "add/add.hpp"
#include "sub/sub.hpp"

int main() {
    std::cout << "hello world" << '\n';
    std::cout << add(1, 2) << '\n';
    std::cout << sub(1, 2) << '\n';

    return 0;
}