#if 0
#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>

int main() {
    auto x = 1;
    std::cout << typeid(x).name() << std::endl;
    auto& r = x;
    std::cout << typeid(x).name() << std::endl;
    auto y = "abc";
    std::cout << typeid(y).name() << std::endl;
    auto z = std::string("def");

    std::cout << typeid(z).name() << std::endl;
//    auto vec = std::vector<int>{1, 2, 3};
    auto vec = std::vector<int>{1,2,3};
    auto iter = vec.begin();
    std::cout << typeid(vec).name() << '\n';


    // 定义一个简单的lambda表达式，它接受一个参数并打印它
    auto print = [](int n){ std::cout << n << " "; };
    //[](int n){ std::cout << n << " "; }(5);


    // 创建一个vector并使用lambda打印每个元素
    std::vector<int> numbers = {5, 2, 9, 1, 5, 6};
    std::for_each(numbers.begin(), numbers.end(), print);
    std::cout << "\n";

    // 使用lambda进行条件过滤，捕获外部变量
    int threshold = 4;
    std::vector<int> filtered;
    std::copy_if(numbers.begin(), numbers.end(),
                 std::back_inserter(filtered),
                 [threshold](int x) { return x > threshold; });

    // 打印过滤后的结果
    std::cout << "Numbers greater than " << threshold << ": ";
    std::for_each(filtered.begin(), filtered.end(), print);
    std::cout << "\n";

    // 嵌套lambda - 计算每个元素的平方，然后求和
    int sumOfSquares = 0;
    std::for_each(numbers.begin(), numbers.end(),
                  [&sumOfSquares](int x) {
                      sumOfSquares += [&x] {
                          int square = x * x;
                          return square;
                      }(); // 立即调用lambda计算平方
                  });

    std::cout << "Sum of squares: " << sumOfSquares << std::endl;

    // Lambda作为比较函数用于排序
    std::sort(numbers.begin(), numbers.end(),
              [](int a, int b) { return a > b; });  // 降序排序

    std::cout << "Sorted in descending order: ";
    std::for_each(numbers.begin(), numbers.end(), print);
    std::cout << "\n";

    return 0;
}
#endif

#include <iostream>
#include <cstring>
#include <utility>  // for std::move

class MyString {
private:
    char* m_data;
    size_t m_size;

public:
    // 常规构造函数
    MyString(const char* str = nullptr) {
        m_size = (str ? std::strlen(str) : 0);
        m_data = new char[m_size + 1];
        if (str) std::strcpy(m_data, str);
        else m_data[0] = '\0';
        std::cout << "Constructed: " << m_data << std::endl;
    }

#if 0
    // 拷贝构造函数
    MyString(const MyString& other) {
        m_size = other.m_size;
        m_data = new char[m_size + 1];
        std::strcpy(m_data, other.m_data);
        std::cout << "Copy constructed: " << m_data << std::endl;
    }
#endif

    // **移动构造函数**
    MyString(MyString&& other) noexcept : m_data(nullptr), m_size(0) {
        m_data = other.m_data;  // 直接"steal" other的资源
        m_size = other.m_size;
        other.m_data = nullptr; // other不再拥有这些资源
        other.m_size = 0;
        std::cout << "Move constructed: " << m_data << std::endl;
    }

    // 析构函数
    ~MyString() {
        delete[] m_data;
    }

#if 0
    // **移动赋值操作符**
    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            delete[] m_data;  // 释放现有资源
            m_data = other.m_data;
            m_size = other.m_size;
            other.m_data = nullptr;
            other.m_size = 0;
        }
        std::cout << "Move assignment: " << m_data << std::endl;
        return *this;
    }

    // 普通赋值操作符（简化版，不考虑自赋值问题）
    MyString& operator=(const MyString& other) {
        if(this != &other) {
            delete[] m_data;
            m_size = other.m_size;
            m_data = new char[m_size + 1];
            std::strcpy(m_data, other.m_data);
            std::cout << "Copy assignment: " << m_data << std::endl;
        }
        return *this;
    }
#endif

    void print() const {
        std::cout << (m_data ? m_data : "nullptr") << std::endl;
    }

};

// 辅助函数，用于展示右值引用
MyString createString() {
    return MyString("Temporary String");
}

int main() {
#if 0
    MyString str1("Hello");
    MyString str2(str1);            // 拷贝构造
    str1.print();                   // 验证str1未改变
    str2.print();
#endif

    MyString str3 = createString(); // 移动构造，因为createString()返回一个临时对象（右值）
    str3.print();

#if 0
    MyString str4;
    str4 = std::move(str3);         // 移动赋值, str3将不再拥有其资源
    str4.print();
    str3.print();                   // str3现在应该指向nullptr
#endif

    return 0;
}