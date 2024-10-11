#include <iostream>

void modify(int* pa) {
    *pa = 2;
}

void modify1(int pa) {
    pa = 3;
}

// 高并发，高可用，响应快
void functionEnter(void* para) {
    //static_cast<int*>(para);
    //static_cast<xxxx>(para);
}

int main() {
    /*
    int a = 1;
    float b = 2.2f;
    int* pa = & a;
    float* pb = & b;
    std::cout << "pa = " << pa << std::endl;
    std::cout << "pb = " << pb << std::endl;

    std::cout << "a = " << a << std::endl;
    modify(pa);
    std::cout << "a = " << a << std::endl;
    modify1(a);
    std::cout << "a = " << a << std::endl;
    */
    int* ptr = nullptr;
    // int* ptr = 0;

    /*
    int a2 = 5;
    int* pa2 = &a2;
    int** ppa2 = &pa2;
    std::cout << "a2 addr = " << &a2 << std::endl;
    std::cout << "pa2 = " << pa2 << std::endl;
    std::cout << "pa2 addr = " << &pa2 << std::endl;
    std::cout << "ppa2 = " << ppa2 << std::endl;

    // float* px = &a2;
    void* p =  &a2;

    std::cout << *static_cast<int*>(p) << std::endl;
    void* p1 = pa2;
    std::cout << *static_cast<int*>(p1) << std::endl;

    // void** p2 = nullptr;
    */

    /*
    int a4 = 5;
    int& a4r = a4; // int* pa4 = &a4;
    std::cout << "a4r = " << a4r << std::endl;
    std::cout << "a4 addr = " << &a4 << std::endl;
    std::cout << "ar4 addr = " << &a4r << std::endl;

    int a5 = 6;
    int a6 = 7;
    int& a5r = a5; // a5r 就是 a5;
    a5r = a6;
    std::cout << "a5r = "  << a5r << std::endl;
    */
    /*
    int a7 = 10;
    int a8 = 11;
    const int* p1 = &a7;
    int* const p2 = &a7;
    //*p1 = 11;
    p1 = &a8;
    *p2 = 12
    */

    std::cout << "hello \"world" << '\n';
    

    return 0;
}
