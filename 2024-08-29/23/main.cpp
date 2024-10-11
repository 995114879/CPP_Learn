#include <iostream>

class Base {
public:
    int publicVar;
protected:
    int protectedVar;
private:
    int privateVar;

public:
    Base() : publicVar(1), protectedVar(2), privateVar(3) {}

    void show() {
        std::cout << "Base Public: " << publicVar << ", Protected: " << protectedVar << std::endl;
    }
};

class Derived : protected Base {
public:
    void accessBaseMembers() {
        show();
        publicVar = 10;  // OK，可以访问
        protectedVar = 20;  // OK，可以访问
//        privateVar = 30;  // 错误，无法访问基类的 private 成员
    }
};

class Derived2 : public Derived {
public:
    void accessBaseMembers() {
        show();
        publicVar = 3;
    }
};

int main() {
    Derived d;
    d.accessBaseMembers();

    d.show();  // Output: Base Public: 10, Protected: 20
    d.publicVar = 0;

    Derived2 d2;

    return 0;
}