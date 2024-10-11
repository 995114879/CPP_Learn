#include <iostream>

class Test {
    int n;
    short s;
    void greeting() {
        std::cout << "hello world" << std::endl;
    }
};

int main() {
    Test t1;
    std::cout << "empty class size = " << sizeof(t1) << std::endl;

    return 0;
}
