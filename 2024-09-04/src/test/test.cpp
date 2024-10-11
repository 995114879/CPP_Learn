#include <iostream>
#include <cassert>
#include "../add/add.hpp"
#include "../sub/sub.hpp"

int main() {
    assert(add(1, 2)==3);
    assert(sub(1, 2)==0);

    return 0;
}