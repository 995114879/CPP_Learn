#include <iostream>
#include <limits>

// main函数是入口点
// 编译器和运行时的约定
// _XXX
// 嵌入式开发，_XXX1, _XXX2
// ISO C++
//
int main() {
    // << 插入运算符，这个在后面 IO 流的处理的部分会专门详解
    // >> 提取运算符

    char c1 = 'a'; // -128 ~ 127
    char c2 = c1 + 1;
    std::cout << "c1 = " << c1 << std::endl;
    std::cout << sizeof(c1) << std::endl;
    std::cout << (int)c1 << std::endl;
    std::cout << c2 << std::endl; // end of line
    std::cout << "char max =" << (int)std::numeric_limits<char>::max() << std::endl;
    std::cout << "char min =" << (int)std::numeric_limits<char>::min() << std::endl;

    // int 4
    int i1;
    i1 = 1;
    std::cout << "i1 size = " << sizeof(i1) << std::endl;
    std::cout << "i1 size = " << sizeof i1 << std::endl;
    std::cout << "int size = " << sizeof(int) << std::endl; // 运算符是语言内置，函数与之不是一个级别
    std::cout << "int max =" << std::numeric_limits<int>::max() << std::endl;
    std::cout << "int min =" << std::numeric_limits<int>::min() << std::endl; // 模板编程
    // 测试范围
    int i2 = 2147483647;
    int i3 = i2 + 1;
    std::cout << "i3 = " << i3 << std::endl; // 有类型数据范围非常重要

    // float IEEE
    float f1;
    std::cout << "f1 size = " << sizeof(f1) << std::endl;

    std::cout << "float max =" << std::numeric_limits<float>::max() << std::endl;
    std::cout << "float min =" << std::numeric_limits<float>::min() << std::endl; // 模板编程

    f1 = 1.1;
    std::cout << "f1 = " << f1 << std::endl;
    int i4 = f1;
    std::cout << "i4 = " << i4 << std::endl;

    bool b1;
    std::cout << "b1 size = " << sizeof(b1) << std::endl;
    b1 = true;
    std::cout << "b1 = " <<  b1 << std::endl;
    std::cout << "b1 = " << std::boolalpha <<  b1 << std::endl;

    // if (exp => true| false)
    // else
    //
    // void （空） 特殊用处 1. 定义函数的时候
    // void funtion1(xxx) {} 函数无返回值
    // void* 主要用来定义一个类型没有明确的指针
    //void* p; 类型没有明确的指针

    int a = 1;
    int b = 2;
    int c = a + b; // 防止和超出表示范围
    int d = a - b;
    int e = a * b;
    int f = a / b; // => 0
    float g = (float)a/b;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;
    std::cout << "f = " << f << std::endl;
    std::cout << "g = " << g << std::endl;

    // int -> short, 4 -> 2
    short int si;
    std::cout << "short int size = " << sizeof(si) << std::endl;
    std::cout << "short int min =" << std::numeric_limits<short int>::min() << std::endl; // 模板编程

    long int li;
    std::cout << "long int size = " << sizeof(li) << std::endl;

    double di;
    std::cout << "di size = " << sizeof(di) << std::endl;

    std::cout << "double max =" << std::numeric_limits<double>::max() << std::endl;
    std::cout << "double min =" << std::numeric_limits<double>::min() << std::endl; // 模板编程

    // 有符号数 => signed, 无符号数 => unsigned
    unsigned int ui;
    std::cout << "unsigned int size = " << sizeof(ui) << std::endl;
    std::cout << "unsigned int max =" << std::numeric_limits<unsigned int>::max() << std::endl;
    std::cout << "unsigned int min =" << std::numeric_limits<unsigned int>::min() << std::endl; // 模板编程

    return 0;
}

// main函数是入口, 只能有一个。
// 项目里面有很多解决方案，客户端.exe, 服务端.exe