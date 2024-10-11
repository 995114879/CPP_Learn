#include <iostream>

class Test {
private:
    int n;
    short s;
    void greeting() {
        std::cout << "hello world" << std::endl;
    }
};

class SubTest : public Test {

};

class Animal {
public:
    int age;
    void eat() {
        std::cout << "simple eatting" << std::endl;
    }
};

class Dog : public Animal {
public:
    void setAge(int a) { age = a; } // 可以访问 protected 成员
    void eat() {
        std::cout << "dog eatting" << std::endl;
    }
};

int main() {
//    Test t1;
//    std::cout << "empty class size = " << sizeof(t1) << std::endl;
//    SubTest st;
//    st.greeting();
    Dog mydog;
    mydog.eat();

    return 0;
}
