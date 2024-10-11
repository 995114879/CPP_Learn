#include <iostream>

// 回调函数
void printMessage(int num) {
    std::cout << "回调函数被调用，数字为: " << num << std::endl;
}

void printAddoneMessage(int num) {
    std::cout << "after addition: " << num+1 << std::endl;
}

// ------------------------

// 接收回调函数指针作为参数的函数
void processNumber(void (*callback)(int), int num) {
    callback(num);
}

int counter = 0; // 全局变量

void loopPrint() {
    ++counter;
    std::cout << "hello world" << std::endl;
    std::cout << "counter = " << counter << std::endl;
    if (counter == 100) {
        return;
    }
    loopPrint();
}

void test() {
    static int counter = 1;
    std::cout << "counter = " <<  counter << std::endl;
    counter++;
}

int main() {
    /*
    // 我是甲方，我这里产生了一个数字，我需要乙方来处理这个数字
    int numberx = 10;
    processNumber(printMessage, numberx);
    processNumber(printAddoneMessage, numberx);
     */
    // loopPrint();
    // 7 * 24
    int* p = new int[2]; // 不保证一定成功，大型的数据中心里面, 256G内存，80%
    *p = 1;
    std::cout <<"p = " << p << std::endl;
    std::cout <<"*p = " << *p << std::endl;

    /*
    delete p;
    p = nullptr;

    assert(p != nullptr);
     */

    int x; // 4

    test();
    test();
    test();

    

    return 0;
}
