#include <iostream>

struct Test {
    Test() {
        std::cout << "Test()" << std::endl;
    }
    ~Test() {
        std::cout << "~Test()" << std::endl;
    }
    void display() {
        std::cout << "x = " << x  << std::endl;
    }

    void show_this() {
        std::cout << "this = " <<  this << std::endl;
    }

    void setX(int x) {
        //x = x;
        this->x = x;
    }

    int x;
};

class MyClass {
public:
    static int count; // 声明静态成员变量

    static void printCount() { // 声明静态成员函数
        std::cout << "Count: " << count << std::endl;
    }

    MyClass() {
        count++;
    }
};

int MyClass::count = 0;

class MyClass1 {
public:
    const int value; // 声明常量成员变量

    // 构造函数初始化列表中初始化常量成员变量
    //MyClass1(int val) : value(val) {}
    MyClass1(int val) : value(val) {
    }

    int getValue() const { // 声明常量成员函数
        return value;
    }
};

class MyClass2 {
public:
    const int value1;
    int& value2;

    MyClass2(int val1, int& val2) : value1(val1), value2(val2) {}
};



int main() {
    // 最小作用域原则
//    {
//        Test test;
//        test.display(); // => display(&test) => display(this)
//    }
//    Test test;
//    test.show_this();
//    std::cout << "test addr = " <<  &test << std::endl;
//
//    std::cout << "ABC" << std::endl;
    MyClass my1;
    MyClass::printCount();
    MyClass my2;
    MyClass::printCount();



    return 0;
}
