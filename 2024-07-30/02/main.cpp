#include <iostream>
#include <string>
#include <unistd.h>
// coding style -> google
// MS
// 宏定义相当于字符串替换行为，类型不安全
/*
constexpr unsigned long long operator"" _w(unsigned long long value) {
    return 10000*value;
}*/

extern void greet();

int main() {
    /*
    int x = 1; // x => int
    int y = 2;

    if (x == y) {
        std::cout << "x == y" << std::endl;
    }
    else {
        std::cout << "x != y" << std::endl;
    }*/

    /*
    unsigned long long yourBankBalance =2_w;
    if (yourBankBalance > 5_w) {
        std::cout << "You are a rich man" << std::endl;
    } else if (yourBankBalance > 3_w) {
        std::cout << "You are a middle level" << std::endl;
    } else {
        std::cout << "You are a poor man" << std::endl;
    }*/


    /*
    char ch;
    std::cout << "请输入一个字符: ";
    std::cin >> ch; // standard input => keyboard

    if (ch >= 'A' && ch <= 'Z') {
        std::cout << ch << " 是大写字母" << std::endl;
    } else {
        std::cout << ch << " 不是大写字母" << std::endl;
    }*/

    /*
    int testVar = 5; // <= 串口读的数据，
    if (testVar == 1) {
        std::cout << " = 1" << std::endl;
    }
    if (testVar == 2) {
        std::cout << " = 2" << std::endl;
    }
    if (testVar == 3) {
        std::cout << " = 3" << std::endl;
    }
    if (testVar == 4) {
        std::cout << " = 4" << std::endl;
    }
    if (testVar == 5) {
        std::cout << " = 5" << std::endl;
    }
    if (testVar == 1) {
        std::cout << " = 1" << std::endl;
    }*/

    /*
    switch (testVar) {
        case 1:
            std::cout << ".. = 1" << std::endl;
            break;
        case 2:
            std::cout << ".. = 2" << std::endl;
            break;
        case 3:
            std::cout << ".. = 3" << std::endl;
            break;
        case 4:
            std::cout << ".. = 4" << std::endl;
            break;
        case 5:
            std::cout << ".. = 5" << std::endl;
            break;
        default: {
            std::cout << "default = " << std::endl;
        }
    }*/

    //greet();

    /*
    int step = 0;
    while (step < 10) {
        std::cout << "current step = "  << step << std::endl;
        step = step + 1;
        if (step == 5) break;
    }*/

    /*
    int step = 0;
    do {
        std::cout << "current step = "   << step << std::endl;
    } while (step > 0); */
    // 嵌入式环境的代码用于封装一些宏

    /*
    int sum = 0;
    for (int i = 0; i < 10; i++) { // 10 [)
    // for (int i = 0; i < 10; i++) { // 10
        sum += i;
    }
    std::cout << "1 到 10 的和为: " << sum << std::endl;
    */
    /*
    int factorial = 1;

    for (int i = 1; i <= 10; i++) {
        factorial *= i;
    }

    std::cout << "10 的阶乘为: " << factorial << std::endl;
    */

    // 数组
    // int size
    /*
    int arr1[3]; // 数组的大小在定义时明确， 不能是变量
    int arr2[3]{0, 1, 2};
    std::cout << sizeof(arr1) / sizeof(int) << std::endl;
    for (int i = 0; i < sizeof(arr2)/ sizeof(int); i++) {
        std::cout << arr2[i] << std::endl;
    }
    std::cout << arr2[10] << std::endl;
    */
    /*
    char ch1[] = "hello";
    std::cout << strlen(ch1) << std::endl;
    */
    //std::string str1; // 空

    int jump = 0;
    jump_table:
        jump += 1;
        std::cout << "jump = " << jump << std::endl;
        sleep(1);
        goto jump_table;

    return 0;
}
