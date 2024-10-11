#include <iostream>

class Base {
public:
    void print(int a) {
        std::cout << "Base print(int): " << a << std::endl;
    }

    void print(int a, int b) {
        std::cout << "Base print(int, int): " << a << ", " << b << std::endl;
    }

    int data = 10;
};

class Derived : public Base {
public:
    void print(int a) { // 覆盖 Base::print(int)
        std::cout << "Derived print(int): " << a << std::endl;
    }

    int data = 20; // 覆盖 Base::data
};

int main() {
    Derived d;
    d.print(5); // 调用 Derived::print(int)
    d.Base::print(5, 10); // 调用 Base::print(int, int)
    std::cout << "Derived data: " << d.data << std::endl; // 输出 20
    std::cout << "Base data: " << d.Base::data << std::endl; // 输出 10

    return 0;
}