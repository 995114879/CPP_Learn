#if 0
#include <iostream>

#include <iostream>
#include <string>

class MyString {
public:
    MyString(const char* str) : data(new char[strlen(str) + 1]) {
        strcpy(data, str);
        std::cout << "Constructor: " << data << std::endl;
    }

    MyString(const MyString& other) : data(new char[strlen(other.data) + 1]) {
        strcpy(data, other.data);
        std::cout << "Copy Constructor: " << data << std::endl;
    }

    MyString(MyString&& other) noexcept : data(other.data) {
        other.data = nullptr;
        std::cout << "Move Constructor: " << data << std::endl;
    }

    ~MyString() {
        delete[] data;
        data = nullptr;
        std::cout << "Destructor: " << (data ? data : "nullptr") << std::endl;
    }

    void show() {
        if (data) {
            std::cout << data << '\n';
        } else {
            std::cout << "data is null" << '\n';
        }
    }

private:
    char* data;
};

int main() {
    MyString str1("Hello");
    MyString str2 = std::move(str1); // 我这个 str1就在这里用一次，后面不关心了。
    str1.show();
    str2.show();

    return 0;
}
#endif

#if 0
#include <iostream>

int main() {
    int binaryValue = 0b1101; 
    std::cout << binaryValue << std::endl;
    return 0;
}
#endif

#if 0
#include <iostream>

int main() {
    long long largeNumber = 1000000000;
    std::cout << largeNumber << std::endl;
    return 0;
}
#endif

#if 0
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<float> numbers1 = {1.1, 2.2, 3.3, 4.4, 5.5};

    // 使用泛型 Lambda 表达式将每个元素乘以 2
    std::transform(numbers.begin(), numbers.end(), numbers.begin(),
                   [](auto& n) { return n * 2; });

    for (auto n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    std::transform(numbers1.begin(), numbers1.end(), numbers1.begin(),
                   [](auto& n) { return n * 2; });

    for (auto n : numbers1) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    return 0;
}

#endif

#if 0
#include <iostream>

int main() {
    int x = 10;

    // 在捕获表达式中初始化变量 y
    auto lambda = [y = x * 2]() {
        std::cout << y << std::endl;
    };

    lambda();  // 输出 20
    return 0;
}
#endif

#if 0
#include <iostream>

template<typename T>
constexpr T pi = T(3.1415926535897932385L);

template <typename T>
T mystr = T("abc");

int main() {
    std::cout << pi<float> << std::endl;  // 输出 float 类型的 pi 值
    std::cout << pi<double> << std::endl; // 输出 double 类型的 pi 值
    std::cout << mystr<const char*> << std::endl;
    std::cout << mystr<std::string> << std::endl;
    return 0;
}

#endif

#if 0
#include <iostream>

constexpr int factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int BB;

enum Test {
    a = 5,
    b = factorial(5),
};

int main() {
    constexpr int result = factorial(5); // 在编译时计算阶乘
    std::cout << result << std::endl;      // 输出 120

    return 0;
}
#endif

#if 0
#include <iostream>
#include <cstdio> // for gets and fgets

int main() {
    char buffer[10];

    std::cout << "请输入一行文字: ";
    std::gets(buffer); // 不安全的函数调用

    std::cout << "您输入的是: " << buffer << std::endl;

    return 0;
}
#endif

#include <iostream>

[[deprecated("Use newFunction instead")]]
void oldFunction() {
    std::cout << "This function is deprecated." << std::endl;
}

void newFunction() {
    std::cout << "This is the new function." << std::endl;
}

int main() {
    oldFunction(); // 编译器会发出警告信息
    newFunction();
    return 0;
}