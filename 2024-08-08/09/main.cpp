#include <iostream>

void modifyArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] *= 2;
    }
}

//void modifyArray(int* arr, int size) {
//    for (int i = 0; i < size; ++i) {
//        arr[i] *= 2; // arr[i] <=> *(arr + i)
//    }
//}

class Rectangle {
public:
    int width; // 成员变量
    int height;

    int getArea() { // 成员函数

        return width * height;
    }
};

struct Rectangle1 {
    int width; // 成员变量
    int height;

    int getArea() { // 成员函数

        return width * height;
    }

private:

};

//int getArea(const Rectangle& rx) {
//    return rx.width * rx.height;
//}

class Person {
public:
    Person() {
        std::cout << "无参的构造被调用" << "Person()" << std::endl;
        name = "def";
        age = 100;
    }

    Person(const std::string& name, int age) : name(name), age(age) {
        std::cout << "构造函数被调用，姓名：" << name << "，年龄：" << age << std::endl;
    }

    ~Person() {
        std::cout << "析构函数被调用，姓名：" << name << "，年龄：" << age << std::endl;
    }

private:
    std::string name;
    int age;
};

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    modifyArray(arr, 5);

    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " "; // 输出：2 4 6 8 10
    }
    std::cout << std::endl;

    int a = 10;
    int* p = &a; // p[0] = *(p + 0), p[1] <=> *(p + 1)
    std::cout << p[0]<<std::endl;
//    std::cout << p[1] << std::endl;
//    std::cout << p[2] << std::endl;
//    std::cout << p[3] << std::endl;

    int* p1 = new int[5];
    delete[] p1;
    int* p2 = nullptr;
    delete p2;

    int arr1[5] = {1, 2, 3, 4, 5};

    // 尝试访问 arr[5]，越界访问
//    std::cout << "arr[5] = " << arr1[10000] << std::endl; // 可能导致程序崩溃或输出垃圾值

    int a1;
    int b1;
    std::cin >> a1 >> b1;

    std::cout << "a1 + b1 = " << a1 + b1 << std::endl;

    Rectangle r1;
    r1.height = 1;
    r1.width = 2;

    std::cout << r1.getArea() << std::endl;

    Person person{"abc", 1};

    Person person1;

    std::cout << "std::cout size = " << sizeof(std::cout) << std::endl;

    return 0;
}